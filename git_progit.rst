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

  git commit —amend 를 한 후에 뜨는 텍스트에서 커밋 메시지를 수정해주면 됨.

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

**브랜치 : 원래 코드와 상관없이 독립적으로 개발하는 것**

Git의 데이터 저장방식
-----------------------------

Commit하면 git은 커밋개체(Commit Object)를 저장한다.

  - 참고: git object의 종류 3가지

    1. blob : 파일의 내용을 담음

    2. tree : 디렉토리의 이름과 파일내용인 blob 대한 정보를 담고 있음.

    3. commit : commit 내용을 담고 있음.

브랜치 생성하기
----------------------------------

`git branch <브랜치명>`\ 으로 브랜치를 생성한다.

브랜치는 `HEAD`\ 라는 포인터를 가지고 있다. 이 포인터는 지금 작업하는 로컬 브랜치를 가리킨다.
`git branch <브랜치명>` 명령은 브랜치를 만들기만 하고 옮기진 않는다.

`git log --decorate` : `--decorate` 옵션은 브랜치가 어떤 commit을 가리키는지 확인

::

  $ git log --oneline --decorate
  f30ab (HEAD -> master, testing) add feature #32 - ability to add new formats to the central interface
  34ac2 Fixed bug #1328 - stack overflow under certain conditions
  98ca9 The initial commit of my project

브랜치 관리하기
-----------------------------------

* `git branch` : 브랜치 목록보기

* `git branch -v` : 브랜치 목록을 마지막 commit 메시지와 함께 보기

* `git branch --merged` : 이미 merge한 브랜치 목록 확인.
  ``*`` 표시가 없는 브랜치는 다른 브랜치와 merge 했기 때문에 삭제해도 정보를 잃지 않는다.

* `git branch --no-merged` : merge 하지 않은 브랜치 목록 확인.

* `git branch -d <브랜치명>` : merge 된 브랜치 삭제하기(merge 안된 브랜치는 삭제 안됨)

* `git branch -D <브랜치명>` : merge 안 된 브랜치 강제로 삭제하기

브랜치를 바꿔서 작업하기
-----------------------------------

`git checkout <브랜치명>` : 해당 브랜치로 이동한다. `HEAD`\ 가 해당 브랜치를 가리킨다.

브랜치를 옮기고 작업하면, 작업한 내용은 해당 브랜치에만 반영된다.
단, **commit을 해야 변경된 내용이 해당 브랜치에만 반영된다.** commit을 하지 않고 브랜치를 옮기면,
옮긴 다른 브랜치에도 작업한 내용이 반영된다.

  참고: `git stash`\ 를 이용하면, commit 하기 전의 내용을 임시 저장할 수 있다.

`git log --oneline --decorate --graph --all` : 히스토리 출력

예::

  $ git log --oneline --decorate --graph --all
  * c2b9e (HEAD, master) made other changes
  | * 87ab2 (testing) made a change
  |/
  * f30ab add feature #32 - ability to add new formats to the
  * 34ac2 fixed bug #1328 - stack overflow under certain conditions
  * 98ca9 initial commit of my project

브랜치 Merge 하기
-------------------------------

아래 그림의 예에는 브랜치가 3개 있다. `master`, `hotfix`, 'iss53'

.. image:: ./image/branch_merge.png
  :scale: 80 %
  :align: center

(출처: Pro-git Book)

현재 상황에서 `hotfix`와 `iss53` 브랜치에서 각각 commit이 이뤄졌고,
2개 브랜치가 새로 생성된 이후에 `master` 브랜치에서는 commit이 이뤄지지 않았다.

이 상황에서 각 브랜치의 작업 내역을 master 브랜치에 merge 한다.

1. hotfix의 작업내용을 master 브랜치에 Merge 한다.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
`fast-forward` 방식

1. master 브랜치로 checkout 한다. : `git checkout master`

2. hotfix의 내용을 merge 한다. : `git merge hotfix`

  실행코드::

    $ git checkout master
    $ git merge hotfix
    Updating f42c576..3a0874c
    Fast-forward
    index.html | 2 ++
    1 file changed, 2 insertions(+)

master는 hotfix로 갈라진 이후에 작업 내역이 없으므로, 그냥 master의 최신 commit의 위치를
가리키는 포인터를 hotfix의 최신 commit 위치로 바꿔주기만 하면 된다.
이걸 **fast-forward**\ 라고 한다. 실제 쉘 상에도 fast-forward라고 나오는 것을 확인할 수 있다.

hotfix 브랜치는 작업이 완료됐으니 삭제하고, 결과를 보면 아래 그림과 같은 상태가 된다.

.. image:: ./image/branch_merge2.png
  :scale: 80 %
  :align: center

2. 1번을 완료한 후 master 브랜치에 iss53 브랜치 작업 내용을 merge 한다.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

`iss53` 브랜치에서 새로 작업 후 다시 한번 commit을 하면 아래와 같은 상태가 된다.

.. image:: ./image/branch_merge3.png
  :scale: 80 %
  :align: center

이 상태에서 master에 iss53 브랜치의 작업내역을 merge 하는 방법은 1번과 비슷하다.
하지만, 합쳐야 할 master와 iss53 브랜치의 각 마지막 commit이 같은 선상에 있지 않으므로
1번과 같이 단순히 포인터를 옮기는 것만으로는 merge할 수 없다.

이때는 두 commit 내용을 합친 별도의 commit을 만들어줘야 한다.

이 과정에서 3개의 commit이 활용된다. 이 3개 commit을 합쳐서 새로운 commit을 만든다.

  1. master의 최신 commit(위 그림의 C4)

  2. iss53의 최신 commit(위 그림의 C5)

  3. master와 iss53의 공통 조상(위 그림의 C2)

실제코드::

  $ git checkout master
  Switched to branch 'master'
  $ git merge iss53
  Merge made by the 'recursive' strategy.
  README |    1 +
  1 file changed, 1 insertion(+)

merge를 완료하면 아래와 같은 상태가 된다.

.. image:: ./image/branch_merge4.png
  :scale: 80 %
  :align: center

브랜치 충돌
----------------------

merge 하는 두 브랜치에서 같은 파일을 동시에 수정하면, merge가 안되고 Conflict(충돌)메시지를 출력한다.

충돌 예::

  $ git merge iss53
  Auto-merging index.html
  CONFLICT (content): Merge conflict in index.html
  Automatic merge failed; fix conflicts and then commit the result.

이런 경우에 자동으로 merge가 안되니, 충돌된 부분을 수동으로 고치고 merge 해야 한다.
