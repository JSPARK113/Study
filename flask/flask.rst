==========================
The Flask Mega Tutorial
==========================

.. Contents::


Chapter 1: Hello, World!
=============================

- `__init__.py` 파일 만들기

  - `app/__init__.py`: Flask application instance::

      from flask import Flask

      app = Flask(__name__)

      from app import routes

- `routes.py` 파일 만들기

  - `app/routes.py`: Home page route::

      from app import app

      @app.route('/')
      @app.route('/index')
      def index():
          return "Hello, World!"

- Flask 실행


Chapter 2: Templates
=============================

- template html 파일 추가

- app/templates/index.html: Main page template::

    <html>
        <head>
            <title>{{ title }} - Microblog</title>
        </head>
        <body>
            <h1>Hello, {{ user.username }}!</h1>
        </body>
    </html>

- `route.py` 파일 수정

- Conditional Statements

  - `{{ }}`\ 나 `{% %}` 블럭 안에 코드를 작성하면, 변수를 담는 등의 작업을 할 수 있다.

  - 템플릿 태그 사용

    - {% extends “base.html” %} : 맨 위에 써주면 base.html의 내용을 모두 가져와서 사용할 수 있다.

    - base.html에 아래와 같이 써준다면

        - {% block body_script %} {% endblock %}

    - {% extends “base.html” %} 이걸 써준 파일 내에서 저 block을 사용하는 경우에 사이에 들어간 내용이 base.html에서는 저 자리에 들어가게 된다.


Chapter 3: Templates
=============================

- Flask-WTF

- Configuration

  - `config.py`: Secret key configuration::

      import os

      class Config(object):
      SECRET_KEY = os.environ.get('SECRET_KEY') or 'you-will-never-guess'

- `__init__.py` 파일에 config 관련 내용 추가::

    from flask import Flask
    from config import Config # 추가

    app = Flask(__name__)
    app.config.from_object(Config) # 추가

    from app import routes

- Form 사용 - User Login Form

  - `form.py` 파일 생성::

      from flask_wtf import FlaskForm
      from wtforms import StringField, PasswordField, BooleanField, SubmitField
      from wtforms.validators import DataRequired

      class LoginForm(FlaskForm):
      username = StringField('Username', validators=[DataRequired()])
      password = PasswordField('Password', validators=[DataRequired()])
      remember_me = BooleanField('Remember Me')
      submit = SubmitField('Sign In')

  - `validators` 인자는 form에 입력된 데이터의 유효성을 확인한다.
    `DataRequired`\ 는 데이터가 비었는지 아닌지를 확인하는 간단한 옵션이다.

  - HTML에 form 추가하기 - Form Templates

    - `<form>` Element는 web form의 container다.

      - `action` 속성: form에 보내진 정보가 어떤식으로 사용되는지.

      - `method` 속성: HTTP request method를 지정. `get` 혹은 `post` 방식

        - 보통은 post 방식을 많이 사용한다.

      - `novalidate`\ 는 옵션.

    - `form.hidden_tag()`\

      - CRSF 공격을 막아주는 토큰을 포함한 hidden field를 생성한다.

      - hidden field를 생성하고, config로 SECRET_KEY를 생성해주면 나머지는 Flask_WTF가 알아서 한다.

- Form에 대한 Views 파일 생성

  - `app/routes.py`: Login view function::

      from flask import render_template
      from app import app
      from app.forms import LoginForm # 추가

      # ...

      # login form에 대한 내용 추가
      @app.route('/login')
      def login():
          login_form = LoginForm()
          return render_template('login.html', title='Sign In', form=login_form)

form으로 데이터 받기
-----------------------

- `app/routes.py` 파일에 데이터 받는 내용 추가::

    from flask import render_template, flash, redirect

    @app.route('/login', methods=['GET', 'POST'])
    def login():
        form = LoginForm()
        if form.validate_on_submit():
            flash('Login requested for user {}, remember_me={}'.format(
                form.username.data, form.remember_me.data))
            return redirect('/index')
        return render_template('login.html', title='Sign In', form=form)

- `methods` 인수: `get`인지 `post`인지 전달.

  - 지정해주지 않으면 디폴트인 `get`만 가능. 데이터를 보내는 `post` 방식은 에러 발생.

  - `GET`: 클라이언트가 정보를 받기만 함.

  -`POST`: 정보를 주고 받을 수 있음. 즉, 데이터를 보낼 수도 있음.

- `form.validate_on_submit()`

  - 브라우저가 `get` 방식을 사용하면 `False`\ 를 반환한다.

  - 브라우저가 `post` 방식을 사용하고, 지정된 validation 조건을 만족하면 `Ture`\ 를 반환한다.
    하나의 Field라도 validation을 만족하지 않으면 `False`\ 를 반환한다.

- `redirect()`: 자동으로 다른 페이지로 연결

- `falsh()`: message를 저장.

  - `get_flashed_messages` 함수를 통해 한번 호출되면 사라진다.

  - `base.html` 파일 수정: Flashed messages in base template::

      <html>
      <head>
          {% if title %}
          <title>{{ title }} - microblog</title>
          {% else %}
          <title>microblog</title>
          {% endif %}
      </head>
      <body>
          <div>
              Microblog:
              <a href="/index">Home</a>
              <a href="/login">Login</a>
          </div>
          <hr>
          {% with messages = get_flashed_messages() %}
          {% if messages %}
          <ul>
              {% for message in messages %}
              <li>{{ message }}</li>
              {% endfor %}
          </ul>
          {% endif %}
          {% endwith %}
          {% block content %}{% endblock %}
      </body>
      </html>
