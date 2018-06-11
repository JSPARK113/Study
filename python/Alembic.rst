=================================
alembic
=================================

`참고 문서`__

.. __: https://github.com/VeranosTech/docs-korean-alembic/blob/docs-korean/docs/build/tutorial_ko.rst#id18

.. Contents::

마이그레이션 환경 - 환경 생성
==============================

`alembic init`\ 을 이용해서 환경을 생성한다. 마이그레이션 디렉토리가 생성된다.

::

  $ cd yourproject
  $ alembic init alembic

환경의 구조::

  yourproject/
    alembic/
        env.py
        README
        script.py.mako
        versions/
            3512b954651e_add_account.py
            2b1ae634e5cd_add_order_id.py
            3adcc9a56557_rename_username_field.p


.ini 파일 편집
===============================

Alembic은 현재 디렉토리에 `alembic.ini` 파일을 생성, alembic 스크립트가 실행될 때 찾는 파일.
환경설정과 같은 역할을 한다.


마이그레이션 스크립트 생성 - revision
================================================

`alembic revision`\ 을 사용해 새로운 리비전 생성.

리비전에는 upgrade와 downgrade에 대한 정보가 들어있다.

아래 예시에서는 "create account table" 이라는 리비전 파일을 생성한다.

revision 생성::

  $ alembic revision -m "create account table"
  Generating /path/to/yourproject/alembic/versions/1975ea83b712_create_accoun
  t_table.py...done

위 코드를 통해 생성된 파일::

  """create account table

  Revision ID: 1975ea83b712
  Revises:
  Create Date: 2011-11-08 11:40:27.089406

  """

  # revision identifiers, used by Alembic.
  revision = '1975ea83b712'
  down_revision = None
  branch_labels = None

  from alembic import op
  import sqlalchemy as sa

  def upgrade():
      pass

  def downgrade():
      pass

위 파일에 포함돼 있는 것

1. 헤더정보

2. 현재버전
3. "downgrade" 리비전에 대한 식별자
   : 이전 버전으로 되돌리려면 어떤 리비전으로 돌아가야하는지 알려주는 셈
4. 기본 Alembic 디렉티브 임포트
5. `upgrade()` 함수: 이 리비전에서 upgrade 하면 어떤 작업을 실행할지 적어줘야 함.
6. `downgrade()` 함수: 이 리비전에서 downgrade 하면 어떤 작업을 실행할지 적어줘야 함.

* 참고: 일반적으로 upgrade가 필요하며, downgrade()는 리비전을 다운시켜야 할 때만 필요하지만
  작성해두는 것이 좋다.


마이그레이션 스크립트 수정
=============================

위에서 생성한 파일에서 `upgrade()`\ 와 `downgrade()` 함수를 수정해본다.

::

  def upgrade():
      op.create_table(
          'account',
          sa.Column('id', sa.Integer, primary_key=True),
          sa.Column('name', sa.String(50), nullable=False),
          sa.Column('description', sa.Unicode(200)),
      )

  def downgrade():
      op.drop_table('account')


마이그레이션 실행하기
============================

`alembic upgrade`\ 를 이용해 업그레이드를 실행할 수 있다.

`alembic upgrade head`\ 를 사용하면 가장 최신 리비전으로 실행된다.

::

  $ alembic upgrade head
  INFO  [alembic.context] Context class PostgresqlContext.
  INFO  [alembic.context] Will assume transactional DDL.
  INFO  [alembic.context] Running upgrade None -> 1975ea83b712


리비전 식별자
=============================

부분적 리비전 식별자 Partial Revision Identifiers
-----------------------------------------------------------------

리비전 숫자를 명시적으로 참고할 때, 전체가 아닌 부분만을 사용할 수 있다.

아래 예는 `ae1027a6acf` 리비전을 참조하기 위해 `ae1`\ 을 사용했다.
만약 똑같은 숫자로 시작하는 버전이 2개 이상 있으면 동작을 중지하고 알려준다.

예::

  $ alembic upgrade ae1


상대적 마이그레이션 식별자 Relative Migration Identifiers
-----------------------------------------------------------------

현재 버전에서 두 버전을 이동하려면 십진수 값 `+N`\ 을 사용한다::

  $ alembic upgrade +2

다운그레이드는 음수 값을 사용한다::

  $ alembic downgrade -1

특정 리비전을 지정할 수도 있다. 아래 예는 `ae1027a6acf`\ 에서 2단계를 더한 리비전을 가리킨다::

  $ alembic upgrade ae10+2


정보 얻기
==========================

`alembic current` : 현재 리비전 보기::

  $ alembic current
  INFO  [alembic.context] Context class PostgresqlContext.
  INFO  [alembic.context] Will assume transactional DDL.
  Current revision for postgresql://scott:XXXXX@localhost/test: 1975ea83b712 -> ae1027a6acf (head), Add a column

`alembic history` : 히스토리 보기::

  $ alembic history --verbose

  Rev: ae1027a6acf (head)
  Parent: 1975ea83b712
  Path: /path/to/yourproject/alembic/versions/ae1027a6acf_add_a_column.py

      add a column

      Revision ID: ae1027a6acf
      Revises: 1975ea83b712
      Create Date: 2014-11-20 13:02:54.849677

  Rev: 1975ea83b712
  Parent: <base>
  Path: /path/to/yourproject/alembic/versions/1975ea83b712_add_account_table.py

      create account table

      Revision ID: 1975ea83b712
      Revises:
      Create Date: 2014-11-20 13:02:46.257104


다운그레이딩
=================================

`alembic downgrade base` : 아무것도 없던 상태, 시작 시점으로 다운그레이드 할 수 있다::

  $ alembic downgrade base
  INFO  [alembic.context] Context class PostgresqlContext.
  INFO  [alembic.context] Will assume transactional DDL.
  INFO  [alembic.context] Running downgrade ae1027a6acf -> 1975ea83b712
  INFO  [alembic.context] Running downgrade 1975ea83b712 -> None

아무것도 없던 시작 시점을 Alembic에선 `base`\ 라고 부른다.

다시 최신 상태로 업그레이드 하고 싶으면 `alembic upgrade head`\ 를 이용한다.


다음 단계
==============================

대다수의 Alembic 환경은 "autogenerate" 기능을 많이 사용한다. `이 문서`__\ 를 읽어봐라.

.. __: https://veranostech.github.io/docs-korean-alembic/docs/build/output/html/autogenerate.html
