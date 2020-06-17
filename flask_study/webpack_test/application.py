# -*- coding: utf-8 -*-

from flask import *

app = Flask(__name__)

# route 설정
@app.route('/')
def index():
    # main.html 템플릿 렌더링 해서 반환
    return render_template('main.html')


# 앱 직접 실행
if __name__ == '__main__':
    # host, port, debug 모드 설정.
    # debug=True 면 python 파일 수정 시마다 해당 내용이 반영돼서 재시작됨.
    app.run(host='localhost', port=5001, debug=True)
