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
이라고 생각했으나.. 로컬 레포에서 커밋하고 push 하기 전에 `git log -p`를 이용해서 미리 수정 내용을 확인하는 것이 유용했음.

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

### git add의 원리

`git add`를 하면
- index 생성 : 파일 이름 포함. 파일마다 따로 하는 것이 아니라 한 파일에 모든 이름이 다 들어가있음.
- objects 생성 : 파일 내용 포함. 파일마다 따로 생성됨.
- 파일을 복사하면 어떻게 될까?
 	- 파일의 이름이 달라도 파일의 내용이 같으면 같은 object를 가리킨다. index에는 다른 이름으로 들어감.

### objects 파일명의 원리

objects는 내용이 같으면 어떻게 파일명이 같을까?

- `sha1` hash 알고리즘을 통해 파일명이 만들어진다.
	- 두글자를 떼서 디렉토리를 만들고, 그 다음 글자를 따서 파일명을 만드는 원리
	- git은 파일 내용뿐 아니라 다른 정보도 추가해서 hash 알고리즘을 통과시킨다.

### commit의 원리

- commit 메시지 정보가 마치 objects로 저장됨.

- commit 정보 파일의 내용
	- commit한 사람
	- commit 메시지
	- tree와 parent
		- tree : commit에 대한 정보. 커밋마다 다름. 각 버전마다의 스냅샷을 tree로 가지고 있는 것.
		- parent : 이전 커밋의 내용

### objects의 종류

- blob : 파일의 내용을 담음
- tree : 디렉토리의 이름과 파일내용인 blob 대한 정보를 담고 있음.
- commit : commit 내용을 담고 있음.

### git 작업 단계 - 로컬

1. working directory
	- 실제 코딩을 진행하는 곳
2. staging area 혹은 index
	- git add를 한 후에 commit을 기다리고 있는 단계에 있는 곳
3. repository
	- git commit을 한 후의 장소
