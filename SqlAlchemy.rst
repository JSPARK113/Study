===========================
ORM 튜토리얼
===========================

참고: https://veranostech.github.io/docs-korean-sqlalchemy/doc/build/output/html/orm/tutorial_ko.html

.. Contents::

데이터베이스 연결
========================

먼저 데이터베이스를 연결한다. 이 예제에서는 SQLite 데이터베이스를 사용한다.

`create_engine` 명령을 사용한다.

::

  >>> from sqlalchemy import create_engine
  >>> engine = create_engine('sqlite:///:memory:')


매핑(Mapping) 선언
============================

선언 시스템(Declarative system) 데이터베이스 테이블 구성하고,
그 테이블에 매핑될 클래스를 정의한다.

`declarative_base()` 명령어를 이용해서
공통 임포트 모듈에 Base 클래스의 인스턴스를 하나 만든다.

이 클래스를 *declarative base class*\ 라고 한다.

::

  >>> from sqlalchemy.ext.declarative import declarative_base

  >>> Base = declarative_base()

`Base` 클래스를 이용해서 매핑할 클래스를 만든다.

클래스는 `__tablename__` 속성과 `primary_key`\ 가 되는
하나 이상의 `column`\ 이 있어야 한다.

::

  >>> from sqlalchemy import Column, Integer, String
  >>> class User(Base):
  ...     __tablename__ = 'users'
  ...
  ...     id = Column(Integer, primary_key=True)
  ...     name = Column(String)
  ...     fullname = Column(String)
  ...     password = Column(String)
  ...
  ...     def __repr__(self):
  ...        return "<User(name='%s', fullname='%s', password='%s')>" % (
  ...                             self.name, self.fullname, self.password)


스키마 생성
===================================

위에서 선언시스템을 이용해 테이블에 대한 정보(table metadata)를 정의했다.
실제 데이터는 `Table` 객체로 표현된다.

테이블을 생성하는 `CREATE TABLE` 명령을 데이터베이스에 내리기 위해
`MetaData.create_all()` 메서드를 호출하고,
`Engine` 인수를 데이터베이스 연결 소스로 전달한다.

::

  >>> Base.metadata.create_all(engine)
  SELECT ...
  PRAGMA table_info("users")
  ()
  CREATE TABLE users (
      id INTEGER NOT NULL, name VARCHAR,
      fullname VARCHAR,
      password VARCHAR,
      기본 키 (id)
  )
  ()
  COMMIT

* 참고 : SQLite나 PostegreSQL가 아닌 다른 데이터베이스에서 실행하는 경우에는
  CREATE TABLE 명령을 실행할 때 문자열 길이를 String 자료형에
  `Column(String(50))` 처럼 써야 한다.


매핑된 클래스의 인스턴스 생성
==============================

`User` 객체를 생성하고 검사해보자.

::

  >>> ed_user = User(name='ed', fullname='Ed Jones', password='edspassword')
  >>> ed_user.name
  'ed'
  >>> ed_user.password
  'edspassword'
  >>> str(ed_user.id)
  'None'


세션 생성
===========================

데이터베이스에 대한 ORM은 Session을 통해 이용한다.

Session 클래스를 `sessionmaker()`\ 를 통해 정의한다.

::
  >>> from sqlalchemy.orm import sessionmaker
  >>> Session = sessionmaker(bind=engine)


session을 이용한 객체의 추가 및 갱신
=============================================

add
-------------

Session에 `add()`\ 를 통해 객체를 추가한다.

::

  >>> ed_user = User(name='ed', fullname='Ed Jones', password='edspassword')
  >>> session.add(ed_user)

이 시점에 인스턴스는 `pending` 상태다.

  참고: `객체 상태에 대한 간단한 소개`__.

  .. __: https://veranostech.github.io/docs-korean-sqlalchemy/doc/build/output/html/orm/session_state_management_ko.html#session-object-states

* **identity map** : Session에 있는 특정 행에 대한 모든 작업이 같은 데이터 셋에서 작동함.
  특정 기본 키에 대해 동일한 파이썬 객체를 반환한다.

add_all
--------------------

`add_all()`\ 을 이용하면 여러 User 객체를 한 번에 추가할 수 있다.

::

  >>> session.add_all([
  ...     User(name='wendy', fullname='Wendy Williams', password='foobar'),
  ...     User(name='mary', fullname='Mary Contrary', password='xxg527'),
  ...     User(name='fred', fullname='Fred Flinstone', password='blah')])

dirty
----------------

변경된 값 추적::

  >>> session.dirty
  IdentitySet([<User(name='ed', fullname='Ed Jones', password='f8s7ccs')>])

new
----------------------

commit 대기 중인 새로운 객체::

  >>> session.new  # doctest: +SKIP
  IdentitySet([<User(name='wendy', fullname='Wendy Williams', password='foobar')>,
  <User(name='mary', fullname='Mary Contrary', password='xxg527')>,
  <User(name='fred', fullname='Fred Flinstone', password='blah')>])

commit
---------------------

변경 사항을 수정하는 트랜잭션 commit::

  {sql}>>> session.commit()
  UPDATE users SET password=? WHERE users.id = ?
  ('f8s7ccs', 1)
  INSERT INTO users (name, fullname, password) VALUES (?, ?, ?)
  ('wendy', 'Wendy Williams', 'foobar')
  INSERT INTO users (name, fullname, password) VALUES (?, ?, ?)
  ('mary', 'Mary Contrary', 'xxg527')
  INSERT INTO users (name, fullname, password) VALUES (?, ?, ?)
  ('fred', 'Fred Flinstone', 'blah')
  COMMIT

* 트랜잭션: 데이터베이스 관리 시스템또는 유사한 시스템에서의 상호작용 단위

롤백(roll back)
--------------------

되돌리기::

  {sql}>>> session.rollback()
  ROLLBACK
  {stop}


쿼리(query)
==========================

Query 객체는 Session의 `query()` 메서드를 사용해 생성할 수 있다.

Query 객체::

  {sql}>>> for instance in session.query(User):
  ...     print(instance.name, instance.fullname)
  SELECT users.id AS users_id,
          users.name AS users_name,
          users.fullname AS users_fullname,
          users.password AS users_password
  FROM users ORDER BY users.id
  ()
  {stop}ed Ed Jones
  wendy Wendy Williams
  mary Mary Contrary
  fred Fred Flinstone
