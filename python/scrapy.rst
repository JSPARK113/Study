=========================
Scrapy 모듈
=========================

.. Contents::


Scrapy의 구조
===========================

프로젝트의 구조::

  └── crawler
    ├── crawler
    │   ├── __init__.py
    │   ├── __pycache__
    │   ├── items.py
    │   ├── middlewares.py
    │   ├── pipelines.py
    │   ├── settings.py
    │   └── spiders
    │     ├── __init__.py
    │     └── __pycache__
    └── scrapy.cfg

- Spider: 크롤링하는 코드 포함

- selector : 웹페이지 상 특정 HTML element를 선택할 수 있는 매커니즘을 구현한 클래스

  - XPath와 CSS Selector 사용 가능. XPath가 더 권장됨.

- items.py : 스크랩된 데이터들을 담고 있는 컨테이너

- pipelines.py : item으로 구성된 결과를 가공, 저장하는 클래스(getter, setter 개념)

- setting.py : 설정파일


xpath
=====================

Scrapy는 xpath와 css 문법을 지원해준다.

이전에는 사용하지 않은 xpath를 알아본다.

XPath(XML Path Language)는 W3C의 표준으로 확장 생성 언어 문서의 구조를
통해 경로 위에 지정한 구문을 사용하여 항목을 배치하고 처리하는 방법을 기술하는 언어

예::

  <?xml version="1.0" encoding="utf-8"?>
  <wikimedia>
  <projects>
  <project name="Wikipedia" launch="2001-01-05">
    <editions>
    <edition language="English">en.wikipedia.org</edition>
    <edition language="German">de.wikipedia.org</edition>
    <edition language="French">fr.wikipedia.org</edition>
    <edition language="Polish">pl.wikipedia.org</edition>
    </editions>
  </project>
  <project name="Wiktionary" launch="2002-12-12">
    <editions>
    <edition language="English">en.wiktionary.org</edition>
    <edition language="French">fr.wiktionary.org</edition>
    <edition language="Vietnamese">vi.wiktionary.org</edition>
    <edition language="Turkish">tr.wiktionary.org</edition>
    </editions>
  </project>
  </projects>
  </wikimedia>

- 모든 project 요소의 name 속성을 선택

  `/wikimedia/projects/project/@name`

- 모든 영문 Wikimedia 프로젝트의 주소(language 속성이 English인
  모든 edition 요소의 문자열)를 선택

  `/wikimedia/projects/project/editions/edition[@language="English"]/text()`

- 모든 위키백과의 주소(Wikipedia의 이름 특성을 가진 project 요소 아래에 존재하는
  모든 edition 요소의 문자열)를 선택

  `/wikimedia/projects/project[@name="Wikipedia"]/editions/edition/text()`

* selector

  1. // : 가장 상위 element

  2. . : 현재 element

  3. ``*`` : 조건에 맞는 앞부분의 하위 element 모두 살펴봄.

    - css selector의 space 한칸과 동일한 역할.

  4. element [조건]

    - 키 값에는 @를 붙임

    - p[2] : p element의 두번째 element
      인덱스는 1부터 시작(0 시작 아님)

    - [@(attibute key)="(attribute value)"]

    - [@id="email"] : 아이디 값이 email인 element

    - [@class="pw"] : 클래스 값이 pw인 element

  5. not

    - not(조건) : 조건이 아닌 요소를 찾음.


item 설정
=========================

`item.py`\ 를 다음과 같이 수정한다.

이렇게 하면 TestItem 클래스에는 title, link, desc 데이터 필드가 생성된다.

::

  from scrapy import Item, Field

  class TestItem(Item):
    title = Field()
    link = Field()
    desc = Field()


spiders
===========================

spiders 파일 안에 parse를 어디서 어떻게 할지 정의하는 클래스를 만들어 준다.

::

  import scrapy
  from crawler.items import RankItem # crawler는 프로젝트의 최상위 디렉토리명

  class RankSpider(scrapy.Spider):
      name = "rankspider" # 실행시에 사용하는 이름 scrapy crawl rankspider 식으로 사용
      allowed_domains = ["도메인 이름"]
      start_urls = [
          "크롤링할 URL"
      ]

    # 위에서 명시한 url의 html 내용을 response라는 형태로 받아줌.
    # 그래서 아래 parse 함수에서는 response를 파라미터로 받음.

    def parse(self, response):
        # 아래에 어떻게 파싱할지 적어주면 됨.

scrapy의 실행은 `scrapy crawl 스파이더이름` 명령어 사용.
("스파이더이름"은 바로 위 클래스에 정의된 이름)

파일로 저장하고 싶으면 `scrapy crawl 스파이더이름 -o 파일명.확장자` 명령어 사용.


pipelines
==========================

크롤링된 내용의 행 순서를 바꾸는 등 가공하고 싶다면, `pipelines.py`\ 를 이용하면 된다.

1. `pipelines.py` 파일에 클래스를 생성.

2. `settings.py`\ 설정 변경

  ::

    ITEM_PIPLINES = {
      '최상위디렉토리명.pipelines.클래스명'
    }

    # 클래스명은 `pipelines.py`\ 에서 정의된 클래스

pipelines에 csv나 json 등을 사용하도록 정의하면,
`scrapy crawl 스파이더이름`\ 만 쓰고 부가적으로 저장하는 옵션을 넣지 않아도 알아서 지정된 파일로
저장이 된다.
