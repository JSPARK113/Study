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

- SELECT, FROM, WHERE을 이용해서 join한 테이블 가져오기

6.1 Table and Column References
-----------------------------------------

FROM 절에서 테이블 이름의 alias를 정할 수 있다.

friend 테이블의 alias를 f로 정함::

  SELECT f.firstname FROM friend f WHERE f.state = ’PA’;


6.2 Joined Tables
-------------------------

- 테이블을 여러개로 나누는 것의 장점

  - 수정이 용이

  - 데이터 찾기가 용이

  - 데이터가 한 곳에만 저장됨.

  - 저장 공간이 더 적게 필요함.


6.3 Creating Joined Tables
--------------------------------------

- 각 테이블의 primary key를 정해줌. 보통은 언더스코어(_)를 사용해서(예: `customer_id`)

- postgreSQL은 컬럼이나 테이블 이름 등의 모든 식별자를 소문자로 인식한다.

  - 굳이 대문자를 쓰고 싶으면 쌍따옴표(")로 감싸주면 된다. 하지만 항상 쌍따옴표를 써야하기 때문에 번거로워진다.

  - 식별자는 문자로 시작해야하고, 부호는 언더스코어(_)만 사용할 수 있다.


6.4 Performing Joins
--------------------------------------

- 아래 예는 `salesorder` 테이블의 `order_id` 컬럼을 가져온다.

- salesorder 테이블과 customer 테이블을 함께 사용했다.

- 조건 :

  - customer.name이 ’Fleer Gearworks, Inc.’

  - `alesorder.customer_id = customer.customer_id`

::

  SELECT salesorder.order_id
  FROM salesorder, customer
  WHERE customer.name = ’Fleer Gearworks, Inc.’ AND
        salesorder.customer_id = customer.customer_id;

- 위의 예에서 `customer_id`\ 는 `customer` 테이블과 `alesorder` 테이블 모두에 있어야 한다.

  - 그렇지 않으면, `ERROR: Column \'customer_id\' is ambiguous.` 에러가 나옴.


6.5 Three- and Four-Table Joins
------------------------------------------

3개 테이블의 컬럼을 참조하는데 AS절을 이용해서 컬럼 이름 명시::

  SELECT customer.name AS customer_name,
         employee.name AS employee_name,
         part.name AS part_name
  FROM   salesorder, customer, employee, part
  WHERE  salesorder.customer_id = customer.customer_id AND
         salesorder.employee_id = customer.employee_id AND
         salesorder.part_id = customer.part_id AND
         salesorder.order_id = 14673;

6.6 Additional Join Possibilities
------------------------------------------


6.7 Choosing a Join Key
-----------------------------------

- join key : 테이블 간에 행을 연결해주는 기준

- 문자보다 숫자를 join key로 사용하는 것이 좋은 이유

  - 숫자는 틀릴 위험이 적다.

  - 이름 같은 경우 동명이인이 있으면 join 할 때 구별할 수 없다.

  - (위에 이어서)고객 이름이 바뀌면, 이름을 참조한 모든 것들도 바꿔줘야 한다.

  - 숫자로 join 하는 것이 긴 문자에 대해 join 하는 것보다 훨씬 효율적이다.

  - 숫자가 문자보다 더 적은 용량을 차지한다.

- join key로는 아래 두가지를 사용하는 것이 좋다.

  - 숫자

  - 짧은 코드(문자, 숫자 포함): 특히 코드를 사용하는 것이 좋다.

    - 다만 아래의 경우에는 아닐 수도 있다.

      - 해당 코드의 사용주기가 짧을 때 (예)주문번호 등)

      - 쓸만한 적당한 코드를 만들 수 없을 때

      - 코드를 내부에서만 사용하고, 외부 사용자는 사용 안할 때


6.8 One-to-Many Joins
----------------------------------

- `one-to-one join` : 두 테이블 다 해당 행이 하나씩만 있는 경우

- `one-to-many join` : 한 테이블의 한 행이 다른 테이블에는 여러 행에 사용됨.

  - 예: 한 사용자가 여러 주문을 함.

- `one-to-none join` : 한 테이블에 있는 행이 다른 테이블에서는 안 쓰임.

  - 예: 사용자가 있는데, 주문한 것은 없음.


6.9 Unjoined Tables
---------------------------------

- Cartesian product : WHERE 절을 사용하지 않고 그냥 FROM 절에서 2개 테이블을 가져오면
  모든 행에 대해서 정보를 다 합치는 곱집합(Cartesian product)이 나온다.

  - 이걸 의도하는 경우는 거의 없다.


6.10 Table Aliases and Self-joins
------------------------------------------

`self-join` 사용 예(`customer`\ 를 `c`\ 와 `c2`\ 로 2번 사용)::

  SELECT c2.name
  FROM customer c, customer c2
  WHERE c.customer_id = 648 AND
        c.zipcode = c2.zipcode;

`customer_id`\ 가 648인 customer와 `zipcode`\ 가 같은 customer의 `name`을 select


6.11 Non-equijoins
------------------------------------

- Equijoins : equality(=)를 이용한 가장 일반적인 join.

- non-equijoins : not equlal(<>)을 이용한 join


6.12 Ordering Multiple Parts
--------------------------------------

- 여러 개의 테이블에서 조건을 가져와서 join 할 수 있다.


6.13 Primary and Foreign Keys
--------------------------------------

- `primay key`: 각 테이블에서 join이 될 기준이 되는 고유한 컬럼(예: 고객 정보에서의 고객 아이디)

- `Foreign key`: 복사해올 때 기준이 되는 값(예: 주문서에서 고객 아이디)


Chapter 7 : Numbering Rows
=======================================
