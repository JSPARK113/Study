============================
리스트럭처드텍스트 입문 연습
============================

.. Contents::

맨 앞에 "``.. Contents::``" 라고 적어주면 제목을 자동으로 인식해 목차로 만들어준다.

Structure
---------------

부제목은 제목 밑에 "``----``" 이런식으로 하이픈을 제목 길이 이상으로 적어주면 인식한다.
부제목 길이보다 하이픈(-)을 더 짧게 하면 오류가 난다.

rst 패턴은 웹브라우저로 읽을 수 있는 구조화된 텍스트를 만드는 HTML converter에 의해 해석된다.

기본적인 패턴 **단락**

  스페이스를 2번 주면 단락으로 만들어진다.

    4번주면 한 번 더 들여쓰여진 단락이 된다.

Text styles - inline markup
-----------------------------

텍스트를 두껍게 하거나 이탈릭체로 표시하기 위해 "인라인 마크업"을 사용한다.
  **bold** : "``**bold**``"
  *italics* : "``*italics*``"

백퀀트(`)를 두번 사용하면 인라인 마크업이 적용되지 않는다.
  "````이런식으로 문자 양옆에 백퀀트를 2번씩 써주면 된다.````"

별표(*)를 인라인마크업을 위해 사용하지 않으려면 앞에 백슬래시(``\``)를 사용해야한다.
  예: "``\*``"

Lists - 항목을 나열하는 방식
-------------------------------------

항목을 나열하는 방법 3가지: **enumerated**,
**bulleted**, **definitions**

리스트는 반드시 새로운 단락으로 시작해야한다. 즉, 공백 행 다음에 와야 한다.

  1. **enumerated** 리스트

    숫자나 문자 다음에 점(.)이나 괄호("()")를 사용한다. 아래 종류는 모두 가능
    enumerated list 스타일은 모든 웹브라우저에서 지원하는 것은 아니다.

    1. 숫자

    A. 대문자

    a. 소문자

    I. 로마 대문자

    i. 로마 소문자

    (1) 숫자2

    1) 숫자3

  2. **bulleted** 리스트

    "-", "+", "*"를 사용함.

    * "*" 사용

      - "-" 사용

        + "+" 사용

  3. **definition** 리스트

    용어와 용어설명(정의)으로 이뤄져있다.

    용어
      definition lists 용어와 정의를 결합시킨다.

    방식
     - 용어는 한줄의 구문
     - 정의는 용어에서 한줄이상 들여쓰기 됨. 공백행은 없음

Preformattiong - 사전 포맷팅
-------------------------------------

문단 끝에 "``::``" 이걸 쓰고 한 줄 공백을 만들면 그 다음줄부터는 사전 포맷팅된 블럭안에 들어가게 된다.

예시::

  이런식으로 블럭을 만들게 된다.
  들여쓰기를 유지하면 계속 블럭이 된다.

들여쓰기 안하면 이렇게 블럭에서 빠져나오게 된다.
"``::``" 앞에 단어를 쓰지 않으 블럭 앞에 아무것도 안나옴.

Sections
------------------------

문서를 섹션으로 나누기 위해서 섹션 헤더를 써야 한다.

  === > --- > ~~~ 순서. 포함관계.

  예시::

    섹션 1
    ================
    섹션 1.1
    ----------------
    섹션 1.1.1
    ~~~~~~~~~~~~~~~~~

문서 제목/부제목

  제목::

    ============
    제목
    ============

  부제목::

    --------------
    부제목
    --------------


Images
----------------------

이미지를 삽입 : `image` 명령어 사용
height부터는 부가적인 사항

::

  .. image:: 이미지주소
  :height: 100
  :width: 200
  :scale: 50
  :alt: alternate text


다음 단계
------------------------------

여기까지가 리스트럭처드텍스트의 기본적인 사용법

  - 다음단계: `빠른 reStructuredText`_ 유저 레퍼런스
  - 아주 상세한 정보: `reStructuredText 마크업 설명서`_ \를 살펴봐라.

.. _빠른 reStructuredText:
   https://veranostech.github.io/docs-korean-docutils/docutils/docs/user/rst/quickref_ko.html
.. _reStructuredText 마크업 설명서:
   https://veranostech.github.io/docs-korean-docutils/docutils/docs/ref/rst/restructuredtext_ko.html

링크 걸기
-------------------------------

1. 문장 안에 URL 포함하기 : ```Python <http://www.python.org/>`_.``

- 결과 : `Python <http://www.python.org/>`_.

2. 링크 명 걸지 않고 연결하기. 반드시 한 줄을 띄어야 한다.

::

  Internal crossreferences, like example_.

  .. _example:http://www.python.org/

- 결과: Internal crossreferences, like example_.

.. _example: http://www.python.org/

3. 두 단어 이상의 절을 넣을 때는 `` 사이에 넣어준다.

::

  Python is `my favourite programming language`_.

  .. _my favourite programming language: http://www.python.org/


- 결과 : Python is `my favourite programming language`_.

.. _my favourite programming language: http://www.python.org/
