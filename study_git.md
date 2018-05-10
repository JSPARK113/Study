# 생활코딩 - 지옥에서 온 Git

## git의 기본사용
* git 시작하기
	1. init: git init으로 현재 폴더에서 git을 시작
	2. clone

* .git에는 git의 정보가 들어있는 디렉토리

* git status : 현재 git의 상태를 보여줌.
	- untracked files: 아직 git이 관리하지 않는 파일

* 버전 만들어보기
	- git commit -m "메시지"
	- 혹은 git commit 하고 enter 치면 vim이 켜짐
	- git log : commit한 내용이 기록으로 남음.

* 왜 git은 add와 commit을 나누어 놨을까?
	- 보통은 하나의 파일에 하나의 commit을 하는 것이 이상적.
	- 하지만 commit할 시기를 놓칠 때도 많다.
	- add를 이용해서 원하는 파일만 add한 후 commit을 실행할 수 있다. -> 선택적으로 commit할 수 있다.
	- add를 하면 commit 대기 상태가 됨. -> 이런 상태를 stage area라고 함.

* stage - repository
	- stage : 레포에 올라가기 전에 있는 단계(add만 된 단계)

* git을 사용하면 좋은 점.
	- 히스토리를 알 수 있다.
	- `git log -p` : commit 내역을 보는데, 코드의 차이도 함께 보여줌. commit끼리의 차이점을 보여줌.
	- `git diff 커밋아이디` : 해당 커밋에 대한 자세한 내용을 보여줌.
		- commit은 commit id도 있음.
		- `git diff` 만 치면 이전 커밋 이후에 내가 작업한 코드의 차이점을 보여줌.

*github을 이용하면 git log를 굳이 사용하지 않을듯*

* 과거로 돌아가기
	- `git reset 커밋아이디 --hard`
		- 해당 커밋아이디의 버전으로 돌아감.
		- 웹 상에 공유를 한 후에는(push를 한 후에는) reset을 하면 안됨. 내 컴 레포에 커밋했을 때까지만 reset 가능.
	- git revert 커밋아이디
		- 해당 커밋아이디의 버전으로 돌아감.
		- git reset과이 차이는 추후에 자세히

* git commit 옵션
	- `git commit --help` : 매뉴얼
	- `git commit -a` : 수정하고 삭제한 파일은 자동으로 add 하고 commit 함.
	- `git commit -m 메시지` : 메시지를 vim을 켜지않고 inline에서 작성함.
	- `git commit -am` : 수정,삭제 파일을 add 하고 commit하며 메시지도 줄 수 있다.

## git의 원리

------ 원리 - 분석도구 gistoty 소개 부터 들으면됨. (0510)
