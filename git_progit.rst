================
Git - Pro git
================

--------------------------------------------------
Pro git의 유용한 내용들
--------------------------------------------------

`Pro git - 한국어판`__

.. __ : https://git-scm.com/book/ko/v2


.. Contents::


되돌리기
=================

commit 되돌리기
------------------

`git commit —amend` 사용

1. commit 까지 한 후에 메시지를 수정하고 싶으면

  * git commit —amend 를 한 후에 뜨는 텍스트에서 커밋 메시지를 수정해주면 됨.

2. commit 을 한 후에 파일을 수정해서 해당 커밋에 추가하고 싶으면

  1) 파일을 수정한다.

  2) git add로 해당 파일을 추가한다.

  3) git commit으로 이전 commit의 내용을 수정한다.

  4) 이렇게 하면 이전 버전에서 새로 수정한 내용까지 합쳐서 commit이 나타난다.

add 되돌리기
-----------------

`git reset HEAD <파일이름>` 사용

  : add 했던 파일을 add 하지 않은 상태로 돌려준다.


리모트 저장소
====================

리모트 저장소 : 인터넷이나 네트워크 어딘가에 있는 저장소

리모티 저장소 확인하기
----------------------

`git remote` 명령 이용

  `git remote`\ 만 쓰면 이름만 나온다. (보통 처음에는 `origin`)

  `git remote -v`\ 를 사용하면 단축이름과 URL을 함께 볼 수 있다.

리모트 저장소 추가하기
--------------------------

`git remote add [단축이름] [url]` 사용

예::

  $ git remote
  origin
  $ git remote add pb https://github.com/paulboone/ticgit
  $ git remote -v
  origin	https://github.com/schacon/ticgit (fetch)
  origin	https://github.com/schacon/ticgit (push)
  pb	https://github.com/paulboone/ticgit (fetch)
  pb	https://github.com/paulboone/ticgit (push)

리모트 저장소를 Pull 혹은 Fetch 하기
-------------------------------------

`git fetch [remote-name]`

  :로컬에 없지만, 리모트 저장소에 있는 데이터를 모두 가져온다.
  fetch 하면 이전에 가져온 이후에 수정된 것을 모두 가져오지만, merge 되진 않는다.

`git pull` : 리모트 저장소 브랜치에서 데이터를 가져와서 merge 시킨다.

리모트 저장소에 Push 하기
---------------------------------

`git push [리모트 저장소 이름] [브랜치 이름]`
  : 같은 upstream 저장소에 여러명이 clone을 하면 다른 사람이 작업한 것을
  내가 작업한 것에 먼저 merge 하고나서 push할 수 있다.


Git Alias
---------------------

Git에서도 Alias를 만들 수 있다.

예::

  $ git config --global alias.ci commit
  $ git config --global alias.st status

위처럼 작성하면 `git commit` 대신 `git ci`\ 를,
`git status` 대신 `git st`\ 를 사용할 수 있다.

더 긴 명령어에 대해 작성하려면::

  $ git config --global alias.last 'log -1 HEAD'


Git 브랜치
===========================

원래 코드와 상관없이 독립적으로 개발하는 것

Git의 데이터 저장방식
-----------------------------

Commit하면 git은 커밋개체(Commit Object)를 저장한다.

  - 참고: git object의 종류 3가지

    1. blob : 파일의 내용을 담음

    2. tree : 디렉토리의 이름과 파일내용인 blob 대한 정보를 담고 있음.

    3. commit : commit 내용을 담고 있음.
