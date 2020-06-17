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
