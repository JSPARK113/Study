===========================
postgreSQL
===========================

.. Contents::

Chapter 3 : Basic SQL Commands
========================================

3.1 Relational Databases
----------------------------------

SQL : Structured Query Language DB와 소통할 수 있는 가장 일반적인 방법이며 대부분의
DB 시스템에서 사용가능하다.

DB 안에는 Table이 있다.

- 참고 : `psql -l` : 현재 있는 DB리스트를 볼 수 있음.

- Table : RDBMS의 기초. 데이터를 가지고 있음.

  * row로 리스트 돼 있다.

  * column은 같은 타입의 정보를 담고 있다.

3.2 Creating Tables
----------------------------------

- `CREATE TABLE` : 테이블을 생성하는 쿼리

- `\\d` : 현재 접속한 데이터베이스의 테이블들을 보여줌. 특정 테이블의 정보를 보고 싶으면,
  뒤에 테이블 이름을 붙이면 됨.

3.3 Adding Data with INSERT
---------------------------------------

- `INSERT` 명령문 사용해서 데이터 입력

  - string 타입은 반드시 홑따옴표(\')를 써야함. 쌍따옴표(\")는 작동 안함.

  - string 상태로 따옴표 안에 들어가지 않는 한, 공백, 대문자는 안지켜도 됨.

3.4 Viewing Data with SELECT
-----------------------------------------

- `SELECT` 문으로만 데이터를 볼 수 있다.

  - `SELECT * FROM friend` : * 자리에 원하는 column명, friend에는 테이블명을 넣으면 됨.

3.5 Selecting Specific Rows with WHERE
------------------------------------------

- `SELECT`\ 와 함께, `WHERE`\ 를 사용하면 특정 조건에 맞는 row를 볼 수 있다.

3.6 Removing Data with DELETE
------------------------------------

- `DELETE`\ 를 사용해 row를 지울 수 있다.

- `DELETE FROM friend WHERE age = 19;`

  - friend 테이블에서 나이가 19살인 row를 제거한다.

3.7 Modifying Data with UPDATE
---------------------------------------

`UPDATE`

3.8 Sorting Data with ORDER BY
------------------------------------------

- `ORDER BY` : 원하는 순서로 정렬할 수 있다.

  - 'SELECT * FROM friend ORDER BY age DESC'

    - friend 테이블을 age에 대해 내림차순으로 정렬해서 보여준다.

  - `DESC` : 내림차순

3.9 Destroying Tables
--------------------------------------

- `DROP TABLE` : 테이블 삭제하기

  - 예: `DROP TABLE friend`

    - friend 테이블 삭제

3.10 Summary
----------------------------

- CREATE TABLE

- DROP TABLE

- SELET (& FROM, WHERE)

- INSERT

- UPDATE(& SET)

- DELETE


Chapter 4 : Customizing Queries
=======================================

4.1 Data Types
------------------------

  ============ =======================================
  category     Type
  ============ =======================================
  문자
               - CHAR(length)

               - VARCHAR(length)
  숫자
               - INTEGER

               - FLOAT

               - NUMERIC(precision, decimal)
  ============ =======================================

4.2 Quotes Inside Text
---------------------------------

- 문장 사이에 홑따옴표( ``'`` )를 넣고 싶으면, 홑따옴표를 두번 쓰면됨. 이렇게 "``''``"

- 혹은 앞에 백슬래시를 넣어라. 이렇게 "``\'``"

4.3 Using NULL Values
--------------------------------

- `NULL`

  - INSERT INTO friend VALUES ('jack', 'Burger', NULL);

    - NULL 이라고 쓰면 NULL 값이 들어간다.

- `IS NULL`, `IS NOT NULL` : NULL 값이 있는지 확인

- 빈 값인 ``''``\ 과 NULL 은 다르다.

4.4 Controlling DEFAULT Values
--------------------------------------

- 값을 넣지 않으면 나오는 디폴트 값을 제어할 수 있다.

- DEFAULT를 정의하지 않으면 NULL 값이 디폴트가 된다.

- 테이블을 정의할 때, DEFAULT로 값을 넣어주면된다.

  - 아래처럼 쓰면 time에 디폴트 값으로 CURRENT_TIMESTAMP 값이 들어가게 된다.

  ::

    CREATE TABLE account (
      name    CHAR(20),
      time    TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    );

4.5 Column Labels
-----------------------------------

- `AS` : 컬럼에 라벨을 붙일 수 있다.

- `SELECT firstname AS buddy FROM friend;`

  - `firstname` 컬럼의 이름을 `buddy`\ 로 나타냄

4.6 Comments
-----------------------------------

- ``-- 내용`` : 한줄 comments에 사용

- ``/* 내용 */`` : 여러줄 comments에 사용

4.7 AND/OR Usage
---------------------------

- AND 예시 - firstname이 Sandy고, lastname이 Gleason인 row만 보기::

    SELECT * FROM friend
    WHERE firstname = 'Sandy' AND lastname='Gleason';

- OR 예시 - state가 NJ 거나, PA인 row 보기::

    SELECT * FROM friend
    WHERE state = 'NJ' OR state = 'PA';

- AND나 OR을 여러개 함께 쓸 때는 앞에 부터 적용된다.

  - 괄호로 지정해주면 괄호 안이 먼저 적용된다.

4.8 Range of VALUES
---------------------------------

- 사이의 값을 보고 싶으면 `BETWEEN 값1 AND 값2` 사용

4.9 LIKE Comparison
---------------------------------

- 문자열을 특정 패턴에 맞춰서 봐야할 때

- ``%``\ 나 ``_``\ 를 문자 그대로 쓰고 싶다면 앞에 백슬래시를 써줌.

- firstname이 D로 시작하는 row를 select::

    SELECT * FROM friend
    WHERE firstname like 'D%'

  ===================================== =========================
  Comparison                            Operation
  ===================================== =========================
  D로 시작                                LIKE 'D%'
  D를 포함                                LIKE '%D%'
  D가 두번째에 있음                         LIKE '_D%'
  D로 시작하고 e를 포함                      LIKE 'D%e%'
  D로 시작, e포함, 다음에 f포함               LIKE '_D%'
  D를 포함하지 않음                         NOT LIKE '_D%'
  ===================================== =========================

4.10 Regular Expressions
--------------------------------------------

- 정규표현식 사용 가능.

- 정규표현식의 자세한 내용은 따로 공부하는 것으로

4.11 CASE Clause
--------------------------------
