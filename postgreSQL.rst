===========================
postgreSQL
===========================

.. Contents::

* postgreSQL를 설치하는 가장 간단한 방법은 `postgre.app`\ 을 설치하는 것.

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

  예::

    insert into people values ('mark',25);

  - string 타입은 반드시 홑따옴표(\')를 써야함. 쌍따옴표(\")는 작동 안함.

  - string 상태로 따옴표 안에 들어가지 않는 한, 공백, 대문자는 안지켜도 됨.

3.4 Viewing Data with SELECT
-----------------------------------------

- `SELECT` 문으로만 데이터를 볼 수 있다.

  - `SELECT * FROM friend` : * 자리에 원하는 column명, friend에는 테이블명을 넣으면 됨.

3.5 Selecting Specific Rows with WHERE
------------------------------------------

- `SELECT`\ 와 함께, `WHERE`\ 를 사용하면 특정 조건에 맞는 row를 볼 수 있다.

  예::

    select * from people where age=25;

3.6 Removing Data with DELETE
------------------------------------

- `DELETE`\ 를 사용해 row를 지울 수 있다.

- `DELETE FROM friend WHERE age = 19;`

  - friend 테이블에서 나이가 19살인 row를 제거한다.

3.7 Modifying Data with UPDATE
---------------------------------------

`UPDATE`

- `UPDATE people SET age = 20 WHERE name = 'sue';`

  - name이 'sue'인 행의 age를 20로 변경(UPDATE)한다.


3.8 Sorting Data with ORDER BY
------------------------------------------

- `ORDER BY` : 원하는 순서로 정렬할 수 있다.

  - 'SELECT * FROM friend ORDER BY age DESC'

    - friend 테이블을 age에 대해 내림차순으로 정렬해서 보여준다.

  - `ASC` : 오름차순

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

- 사이의 값을 보고 싶으면 WHERE 절에 `BETWEEN 값1 AND 값2` 사용

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

age가 30 미만이면 ages에 20s라고 표시하고 아니면 30s라고 표시하기::

  SELECT name, age,
  CASE
    WHEN age < 30 then '20s'
    ELSE '30s'
  END
  AS ages
  FROM people;


4.12 Distinct Rows
------------------------------------

`DISTINCT` : 중복제거

- `select distinct age from people;`

  people의 age 컬럼에 있는 모든 값들에 대해 unique 값만 뽑아줌.


4.13 Functions and Operators
----------------------------------


- Functions 함수

  - 0개 이상의 인수를 받을 수 있고, 1개의 값을 반환한다.

  - `psql`\ 의 `\df` 명령어: 모든 함수의 리스트(반환값, 함수명, 인수)

  - `psql`\ 의 `\dd` 명령어: 함수의 이름, 설명

- Operators 연산자

  - 함수와 다른 점들이 있음

    - 이름이 아니라 symbol임

    - 보통 2개의 인수를 받음

    - 보통 인수는 연산자 양옆에 있음.


4.14 SET, SHOW, and RESET
--------------------------------------

- SET

- SHOW

- RESET


Chapter 5 : SQL Aggregates
=======================================

5.1 Aggregates
---------------------------

WHERE 절과 함께 사용

- COUNT, SUM, MAX, MIN, AVG

  * COUNT는 모든 행에서 사용가능, 나머지는 특정 컬럼에서 사용 가능

  * NULL 값은 무시되지만, 모든 값이 NULL이면 결과도 NULL로 나온다.
    (Count는 NULL 값도 무시하지 않고 계산한다.)


5.2 Using GROUP BY
------------------------------

friend 테이블에서 state 컬럼을 기준으로 그룹화하여 age에 대해 min, max, avg를 구한다::

  SELECT state, MIN(age), MAX(age), AVG(age)
  FROM friend
  GROUP BY state
  ORDER BY 4 desc;

5.3 Using HAVING
-------------------------

aggreate한 값에 대해서 조건을 걸어줌.

state 기준으로 count한 값에 대해서 1 초과인 것만 뽑음::

  SELECT state, COUNT(*)
  FROM friend
  GROUP BY state
  HAVING COUNT(*) > 1
  ORDER BY state;

5.4 Query Tips
-------------------------

- 하나의 쿼리에 여러 절을 사용할 때, 각 절을 다른 줄에 쓰는 것이 좋다.

- UPDATE, DELETE, INSERT와 같은 쿼리는 데이터베이스를 수정하기 때문에 조심해야한다.

  - 실행하기 전에 미리 같은 WHERE 절을 미리 SELECT에서 실행해서 확인해보는 것이 좋다.


Chapter 6 : Joining Tables
=======================================

여러 테이블에서 데이터 가져오기

6.1 Table and Column References
-----------------------------------------

FROM 절에서 테이블 이름의 alias를 정할 수 있다.

friend 테이블의 alias를 f로 정함::

  SELECT f.firstname FROM friend f WHERE f.state = ’PA’;
