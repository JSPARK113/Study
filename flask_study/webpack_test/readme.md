# flask

### app 정의 하기

```
from flask import *

app = Flask(__name__)
```

### route 설정하기
* 데코레이터 사용: `@app.route('/')`
	* 참고: [데코레이터](https://wikidocs.net/23106)
* 여러 형태로 반환
	* 텍스트 자체를 반환
	* 렌더링한 html 파일 반환
		* html 파일에 `jinja2` 사용하기
			* [기본문법](https://jinja.palletsprojects.com/en/2.10.x/templates/)
	* json 형식의 데이터 반환

### 앱 실행하기
```
if __name__ == '__main__':
    app.run(host='localhost', port=5001, debug=True)
```
* host, port, debug 모드 등 원하는 대로 설정 가능
* debug=True 면 python 파일 수정 시마다 해당 내용이 반영돼서 재시작됨.

### flask 튜토리얼
* [The Flask Mega-Tutorial](https://blog.miguelgrinberg.com/post/the-flask-mega-tutorial-part-i-hello-world)
* [documentation](http://flask.palletsprojects.com/en/1.1.x/)

### atom 플러그인 설치
* [유용한 플러그인 모음](http://superjang.com/archives/3105)


# Webpack

* webpack은 static 파일 번들링 도구
* 공식문서: https://webpack.js.org/concepts/

### webpack을 통한 static 파일 빌드
* `package.json` 파일이 있는 static 디렉토리 안에서 명령 실행
  * `$ npm run build`: 현재 static 파일들을 한번 빌드
  * `$ npm run start`: webpack 서버를 띄우고 static 파일에 변화가 있을 때마다 자동으로 빌드 실행
* 기본개념
	* requirements
		* 필요 패키지 설치(npm 사용)
		* `package.json` 구성
	* Entry
	* Output
	* Loaders: 보통 번들링 전, 중간에 개별 파일단위로 영향
	* Plugins: 번들링 단위로 영향, 보통 번들링 생성 시에 작동
