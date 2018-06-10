=====================
파이썬 로깅
=====================

.. Contents::

참고:

  - `로깅 하우투<https://veranostech.github.io/docs-korean-cpython/Doc/build/html/howto/logging_ko.html>`_

  - `파이썬 로그 기능<https://veranostech.github.io/docs-korean-cpython/Doc/build/html/library/logging_ko.html>`_

로깅: 어떤 소프트웨어가 실행될 때 발생하는 이벤트를 추적하는 수단

  간단한 로깅을 위해 제공하는 함수: 아래로 갈수록 중요하고 치명적임

    - debug() : `DEBUG` : 상세한 정보, 단순히 진단을 하는 것에만 관심이 있을 때.

    - info() : `INFO` : 작업이 예상한대로 흘러가는지 확인 할 때.

    - warning() : `WARNING`(디폴트 레벨)
      : 예상하지 못한 일이 발생한 것을 나타낼 때, 또는 근시일에 어떤 문제가 발생할 것을 나타낼 때. (예. ‘디스크 공간이 적음’) 소프트웨어는 계속 예상한대로 작동중이다.

    - error() : `ERROR` : 더 심각한 문제 때문에, 소프트웨어가 특정한 기능을 더 이상 수행할 수 없을 때.

    - critical() : `CRITICAL` : 심각한 에러, 프로그램이 작동을 더이상 할 수 없음을 나타낼 때

파일에 로깅하기
------------------------

로깅이벤트를 파일에 기록하기

입력::

  import logging
  logging.basicConfig(filename='example.log',level=logging.DEBUG)
  logging.debug('This message should go to the log file')
  logging.info('So should this')
  logging.warning('And this, too')

파일 안에 들어가는 결과::

  DEBUG:root:This message should go to the log file
  INFO:root:So should this
  WARNING:root:And this, too
