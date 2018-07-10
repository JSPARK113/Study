==========================
The Flask Mega Tutorial
==========================

.. Contents:: 목차


Chapter 1: Hello, World!
=============================

- Flask Application

  - application은 패키지 안에 존재한다. `__init__.py` 파일이 있는 디렉토리를 패키지로 인식하고, import 할 수 있으므로 이 파일을 만든다.

  - 패키지를 import 할 때, `__init__.py` 파일이 패키지가 어떤 심볼을 노출할지 정의하고 실행한다.

  - `__init__.py` 파일 만들기.

    - `app/__init__.py`: Flask application instance::

        from flask import Flask # Falsk 클래스 임포트

        app = Flask(__name__) # WSGI 애플리케이dj

        from app import routes

    - `어플리케이션 객체에 대한 설명 <https://flask-docs-kr.readthedocs.io/ko/latest/ko/api.html#flask.Flask>`_

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
            <title>{{ title }} - eblog</title>
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

- `methods` 인수: `get`\ 인지 `post`\ 인지 전달.

  - 지정해주지 않으면 디폴트인 `get`\ 만 가능. 데이터를 보내는 `post` 방식은 에러 발생.

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
          <title>{{ title }} - eblog</title>
          {% else %}
          <title>eblog</title>
          {% endif %}
      </head>
      <body>
          <div>
              eblog:
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

- 유효성 검사하기

  - `app/templates/login.html`\ 에 추가: Validation errors in login form template::

      <p>
          {{ form.username.label }}<br>
          {{ form.username(size=32) }}<br>
          {% for error in form.username.errors %}
          <span style="color: red;">[{{ error }}]</span>
          {% endfor %}
      </p>
      <p>
          {{ form.password.label }}<br>
          {{ form.password(size=32) }}<br>
          {% for error in form.password.errors %}
          <span style="color: red;">[{{ error }}]</span>
          {% endfor %}
      </p>

  - form에 위와 같이 error를 추가

- 링크 생성: url_for()

  - view function을 기반으로 URL을 만들어주는 것이 `url_for()` 함수

  - html나 view 함수의 redirect 함수에도 URL을 직접쓰는 것이 아니라
    `url_for()`\ 를 이용해서 써주는 것이 좋다.

  - 예::

      <div><a href="{{ url_for('index') }}">Home</a></div>
      <div><a href="{{ url_for('login') }}">Login</a></div>

Chapter 4: Database
=============================

- 이 튜토리얼에서는 SQLite, SQLAlchemy를 사용한다.

  - 필요 패키지

  - Flask-SQLAlchemy: `pip install flask-sqlalchemy`

  - Flask-Migrate: `pip install flask-migrate`

- `Flask-SQLAlchemy` 설정::

    import os
    basedir = os.path.abspath(os.path.dirname(__file__))

    class Config(object):
        SECRET_KEY = os.environ.get('SECRET_KEY') or 'you-will-never-guess'
        # sqlalchemy 설정
        SQLALCHEMY_DATABASE_URI = os.environ.get('DATABASE_URL') or \
            'sqlite:///' + os.path.join(basedir, 'app.db')
        SQLALCHEMY_TRACK_MODIFICATIONS = False

  - `SQLALCHEMY_DATABASE_URI`: DB 위치를 받는다.

  - `SQLALCHEMY_TRACK_MODIFICATIONS`: DB의 변화에 대한 신호를 계속 보낼지 설정

- DB가 DB 인스턴스를 통해 보여지도록한다.

  - app/__init__.py: Flask-SQLAlchemy and Flask-Migrate initialization::

      from flask import Flask
      from config import Config
      from flask_sqlalchemy import SQLAlchemy  # 추가
      from flask_migrate import Migrate  # 추가

      app = Flask(__name__)
      app.config.from_object(Config)
      db = SQLAlchemy(app)  # 추가
      migrate = Migrate(app, db)  # 추가

      from app import routes, models  # models 추가

    - `db` 객체: DB를 나타냄

    - `migrate`: 마이그레이션 엔진

    - `models`: DB 구조를 정의

Database models
---------------------

- 데이터는 데이터베이스 안의 `database models`\ 라고 하는 클래스로 나타내진다.

- SQLAlchemy의 ORM 레이어는 데이터베이스 테이블의 각 행과 연결된다.

- `WWW SQL Designer <http://ondras.zarovi.cz/sql/demo/>`_: sql 스키마를 그릴 수 있다.

  - 튜토리얼에서는 `user` 테이블 생성

    - field 정의

      - `id`: primary_key

      - `username`: VARCHAR(64)

      - `email`: VARCHAR(120)

      - `password_hash`: VARCHAR(128) / 패스워드는 보안상 그대로 받으면 안되기 때문에 해시태그로 받는다.

- app/models.py: User database model / 파일 생성::

    from app import db

    class User(db.Model):
        id = db.Column(db.Integer, primary_key=True)
        username = db.Column(db.String(64), index=True, unique=True)
        email = db.Column(db.String(120), index=True, unique=True)
        password_hash = db.Column(db.String(128))

        def __repr__(self):
            return '<User {}>'.format(self.username)

  - `User` 클래스는 `db.Model` 클래스를 상속받는다.

  - 각 필드는 `db.Column`\ 으로 생성. 필드 타입을 인수로 받는다.

  - `__repr__` 메서드: 이 클래스의 객체가 어떻게 print될지 지정.


Mirgration - Alembic 이용
-----------------------------

- 위에서 간단한 데이터베이스 스키마를 작성했지만, 어플리케이션의 규모는 더 커질 수 있다.

- 데이터베이스 구조 변경을 쉽게 반영할 수 있도록 해주는 것이 `Alembic`

- Alembic

  - migration repository를 생성해서 변경사항을 저장한다.

- `flask db`: DB를 관리하는 명령어

  - `flask db init`: DB 마이그레이션 레포를 생성하기 위한 명령어. `migration` 디렉토리가 생성된다.

- 마이그레이션 레포 생성 후 마이그레이션(=DB 생성) 하기

  - `flask db migrate`: alembic 버전 생성

    - 끝에 `-m "메시지"`\ 를 넣으면 마이그레이션 메시지도 넣을 수 있다.

    - Alembic에는 DB의 변경사항을 실행해주는 파이썬 파일이 'versions' 디렉토리에 저장된다.

- `flask db upgrade`\ 를 통해 DB에 Alembic 버전을 적용할 수 있다.

  - `downgrade`\ 도 가능.


Database Relationships
--------------------------

- 데이터 테이블 간의 관계 생성

- 위 예에서 user 테이블의 id를 post 테이블의 user_id를 ForeignKey로 사용한다.

  - "one to many"

- `app/models.py`: Posts database table and relationship::

    from datetime import datetime  # 추가
    from app import db

    class User(db.Model):
        id = db.Column(db.Integer, primary_key=True)
        username = db.Column(db.String(64), index=True, unique=True)
        email = db.Column(db.String(120), index=True, unique=True)
        password_hash = db.Column(db.String(128))
        posts = db.relationship('Post', backref='author', lazy='dynamic')  # 추가

        def __repr__(self):
            return '<User {}>'.format(self.username)

    # Post 테이블 생성. user_id를 User 테이블의 id와 연결해 ForeignKey로 사용한다.

    class Post(db.Model):
        id = db.Column(db.Integer, primary_key=True)
        body = db.Column(db.String(140))
        timestamp = db.Column(db.DateTime, index=True, default=datetime.utcnow)
        user_id = db.Column(db.Integer, db.ForeignKey('user.id'))

        def __repr__(self):
            return '<Post {}>'.format(self.body)

  - 참고: 테이블명은 대소문자를 구분하지 않고 모두 **소문자**\ 로 표시된다.
    따라서 대문자로 시작하는 클래스명을 만들어도, 테이블명은 모두 소문자로 생성된다.

  - `db.relationship()`: User 테이블과 Post 테이블을 연결하기 위해서 사용하는 메서드

    - "one" 측 테이블에 정의한다.

    - user 클래스에서 위의 `relationship()`\ 으로 정의한 `posts`\ 에 접근하면(`u.posts` 이런식으로) 해당 user가 작성한 post가 모두 불러진다.

    - arguments

      - 첫번째 인수: "many" 측 클래스(테이블)

      - `backref`: "many" 클래스에 돌려줄 필드명 지정 (위 예에서 `post.author`\ 은 post 작성자를 반환한다.)

  - 위 예에서 User 클래스에 새로 생성된 `posts` 필드는 실제 필드는 아니다.

- 새로운 테이블이 추가됐으니 다시 migrate 함.

  - alembic 버전 생성: `flask db migrate -m "posts table"`

  - migration: `flask db upgrade`


모델을 페이지에 적용하기
-------------------------

- `db.session`\ 을 통해 데이터베이스 이용

  - python 프롬프트에서 다음과 같이 실행::

      >>> from app import db
      >>> from app.models import User, Post
      # user 생성
      # john
      >>> u = User(username='john', email='john@example.com')
      >>> db.session.add(u)
      >>> db.session.commit()
      # susan
      >>> u = User(username='susan', email='susan@example.com')
      >>> db.session.add(u)
      >>> db.session.commit()

  - `db.session.delete()`: 데이터 삭제

- 모델의 `query` attribute를 이용해 데이터를 불러올 수 있다::

    >>> users = User.query.all()
    >>> users
    [<User john>, <User susan>]
    >>> for u in users:
    ...     print(u.id, u.username)
    ...
    1 john
    2 susan

- ForeignKey를 가진 `Post` 테이블에도 데이터를 넣어보자

    >>> u = User.query.get(1)
    >>> p = Post(body='my first post!', author=u)
    >>> db.session.add(p)
    >>> db.session.commit()

  - post 테이블의 `timestamp` 필드는 자동으로 생성된다.

  - `author`\ 은 `User` 클래스에서 `db.relationship`\ 으로 지정해준 필드


Shell Context
----------------------

- `flask shell`: 쉘 상에서 flask의 기능을 사용할 수 있도록 한 파이썬 인터프리터를 작동시킨다.

- `@app.shell_context_processor` decorator는 함수를 shell context 함수로 등록한다.

- `eblog.py` 파일에 코드 추가::

    from app import app, db
    from app.models import User, Post

    @app.shell_context_processor
    def make_shell_context():
        return {'db': db, 'User': User, 'Post': Post}


Chapter 5: User Logins
=============================

Password Hashing
---------------------

- `Werkzeug`: password hasing 해주는 패키지, flask와는 독립된 모듈.

  - `generate_password_hash`: hash 생성

  - `check_password_hash`: hash 체크

  - 예::

      >>> from werkzeug.security import generate_password_hash, check_password_hash
      >>> hash = generate_password_hash('foobar')
      >>> check_password_hash(hash, 'foobar')

- flask 적용. 모델의 `User` 클래스에 적용::

  - app/models.py: Password hashing and verification::

      from werkzeug.security import generate_password_hash, check_password_hash

      # ...

      class User(db.Model):
          # ...

          def set_password(self, password):
              self.password_hash = generate_password_hash(password)

          def check_password(self, password):
              return check_password_hash(self.password_hash, password)

  - 위처럼 적용하면 사용자 클래스에서 `set_password`\ 해서 패스워드를 생성하고,
    `check_password`\ 를 통해서 해당 사용자의 패스워드가 맞는지 확인할 수 있다.


Falsk에서 로그인 하기
------------------------------

- `Flask-Login`\ 을 사용한다.

  - `pip install flask-login`\ 으로 설치한다.

- app/__init__.py: Flask-Login initialization::

    # ...
    from flask_login import LoginManager

    app = Flask(__name__)
    # ...
    login = LoginManager(app)

    # ...

- `UserMixin` 클래스를 `Flask-Login`\ 이 제공: 일반적인 유저 모델에 사용할 수 있음.

  - app/models.py: Flask-Login user mixin class::

      # ...
      from flask_login import UserMixin

      class User(UserMixin, db.Model):
          # ...

- Loader Function: DB에서 사용자 정보 가져오기

  - `@login.user_loader` 데코레이터 사용

  - app/models.py: Flask-Login user loader function::

      from app import login
      # ...

      @login.user_loader
      def load_user(id):
          return User.query.get(int(id))

-   view function에서 로그인 기능 구현하기

  - app/routes.py: Login view function logic::

      # ...
      from flask_login import current_user, login_user
      from app.models import User

      # ...

      @app.route('/login', methods=['GET', 'POST'])
      def login():
          if current_user.is_authenticated:
              return redirect(url_for('index'))
          form = LoginForm()
          if form.validate_on_submit():
              # User 클래스에서 해당 username을 가진 '첫번째' 데이터를 가져옴.
              user = User.query.filter_by(username=form.username.data).first()
              if user is None or not user.check_password(form.password.data):
                  flash('Invalid username or password')
                  return redirect(url_for('login'))
              login_user(user, remember=form.remember_me.data)
              return redirect(url_for('index'))
          return render_template('login.html', title='Sign In', form=form)

  - `is_authenticated`: 현재 사용자(`current_user`)가 로그인 상태인지 아닌지 파악

  - `check_password`: 입력한 패스워드가 맞는지 체크

  - username과 password가 둘 다 맞으면 `login_user` 함수 실행

로그아웃
-------------------

- `logout_user()`: 실행 시 로그아웃

- app/routes.py: Logout view function::

    # ...
    from flask_login import logout_user

    # ...

    @app.route('/logout')
    def logout():
        logout_user()
        return redirect(url_for('index'))

- 로그인 시 네비게이션 바에 로그아웃 버튼 생성

  - app/templates/base.html: Conditional login and logout links::

      <div>
          eblog:
          <a href="{{ url_for('index') }}">Home</a>
          {% if current_user.is_anonymous %}
          <a href="{{ url_for('login') }}">Login</a>
          {% else %}
          <a href="{{ url_for('logout') }}">Logout</a>
          {% endif %}
      </div>

  - `is_anonymous`: 유저가 로그인 하지 않았을 때 `True`

로그인한 유저만 볼 수 있는 페이지 만들기
------------------------------------------

- 페이지를 보기(view) 전에 로그인한 사용자인지 확인

  - app/__init__.py::

      # ...
      login = LoginManager(app)
      login.login_view = 'login'

  - `login` 변수는 함수

- `@login_required` 데코레이터 사용 @view function

- app/routes.py: @login\_required decorator::

    from flask_login import login_required

    @app.route('/')
    @app.route('/index')
    @login_required
    def index():
        # ...

- 로그인 한 후 다음 페이지에 어떤 것을 보일 것인가?

  - app/routes.py: Redirect to "next" page::

      from flask import request
      from werkzeug.urls import url_parse

      @app.route('/login', methods=['GET', 'POST'])
      def login():
          # ...
          if form.validate_on_submit():
              user = User.query.filter_by(username=form.username.data).first()
              if user is None or not user.check_password(form.password.data):
                  flash('Invalid username or password')
                  return redirect(url_for('login'))
              login_user(user, remember=form.remember_me.data)
              next_page = request.args.get('next')
              if not next_page or url_parse(next_page).netloc != '':
                  next_page = url_for('index')
              return redirect(next_page)
          # ...

템플릿에 유저 정보 표시하기
--------------------------------------

- 현재 유저 표시하기

  - app/templates/index.html: Pass current user to template::

      {% extends "base.html" %}

      {% block content %}
          <h1>Hi, {{ current_user.username }}!</h1>
          {% for post in posts %}
          <div><p>{{ post.author.username }} says: <b>{{ post.body }}</b></p></div>
          {% endfor %}
      {% endblock %}


가입창 만들기
-------------------------

- app/forms.py: User registration form::

    from flask_wtf import FlaskForm
    from wtforms import StringField, PasswordField, BooleanField, SubmitField
    from wtforms.validators import ValidationError, DataRequired, Email, EqualTo
    from app.models import User

    # ...

    class RegistrationForm(FlaskForm):
        username = StringField('Username', validators=[DataRequired()])
        email = StringField('Email', validators=[DataRequired(), Email()])
        password = PasswordField('Password', validators=[DataRequired()])
        password2 = PasswordField(
            'Repeat Password', validators=[DataRequired(), EqualTo('password')])
        submit = SubmitField('Register')

        def validate_username(self, username):
            user = User.query.filter_by(username=username.data).first()
            if user is not None:
                raise ValidationError('Please use a different username.')

        def validate_email(self, email):
            user = User.query.filter_by(email=email.data).first()
            if user is not None:
                raise ValidationError('Please use a different email address.')


Chapter 6: Profile Page and Avatars
=============================================

- 프로필 페이지 만들기

  - app/routes.py: User profile view function::

      @app.route('/user/<username>')
      @login_required
      def user(username):
          user = User.query.filter_by(username=username).first_or_404()
          posts = [
              {'author': user, 'body': 'Test post #1'},
              {'author': user, 'body': 'Test post #2'}
          ]
          return render_template('user.html', user=user, posts=posts)

  - `@app.route` 데코레이터에 URL이 들어갈 때 <> 안에 들어가게 되면 아래 함수에서 인수로 사용한다.

  - `first_or_404()`: 쿼리로 찾은 결과가 있으면 첫번째 값을 반환, 없으면 404에러를 발생시킨다.

- 프로필 사진 추가하기

  - `Gravatar`: 글이나 댓글 등 사용자가 사용하는 서비스에 사진을 넣어줌.(내가 만든 예제에서는 추가하지 않음.)

    - 사이트: http://ko.gravatar.com/

- 포스트용 템플릿 만들기: 프로필 페이지에 포스트 내용을 함께 보여줄 건데,
  모두 같은 형식을 가지고 있다면 템플릿을 따로 만들고
  프로필 페이지 템플릿에는 `Jinja2`\ 의 `include`\ 를 사용하는 것이 낫다.

  - app/templates/_post.html: Post sub-template::

      <table>
          <tr valign="top">
              <td>{{ post.author.username }} says:<br>{{ post.body }}</td>
          </tr>
      </table>


  - app/templates/user.html: User avatars in posts::

      {% extends "base.html" %}

      {% block content %}
          <table>
              <tr valign="top">
                  <td><h1>User: {{ user.username }}</h1></td>
              </tr>
          </table>
          <hr>
          {% for post in posts %}
              {% include '_post.html' %}
          {% endfor %}
      {% endblock %}

- 사용자가 프로필에 추가적인 내용을 쓸 수 있도록 변경

  - app/models.py: New fields in user model::

      class User(UserMixin, db.Model):
          # ...
          about_me = db.Column(db.String(140))
          last_seen = db.Column(db.DateTime, default=datetime.utcnow)

  - 모델을 변경했으니 migration 필요. 코맨드 입력

    - 알렘빅에 새로운 버전 추가::

        flask db migrate -m "new fields in user model"

    - migrate 진행: `flask db upgrade`

- app/templates/user.html: Show user information in user profile template::

    {% extends "base.html" %}

    {% block content %}
        <table>
            <tr valign="top">
                <td><img src="{{ user.avatar(128) }}"></td>
                <td>
                    <h1>User: {{ user.username }}</h1>
                    {% if user.about_me %}<p>{{ user.about_me }}</p>{% endif %}
                    {% if user.last_seen %}<p>Last seen on: {{ user.last_seen }}</p>{% endif %}
                </td>
            </tr>
        </table>
        ...
    {% endblock %}

- 마지막 방문날짜 기록하기

  - `@before_request` 데코레이터: `current_user`\ 가 로그인 상태이면 `last_seen` 필드에 현재 시각을 세팅함.

  - app/routes.py: Record time of last visit::

      from datetime import datetime

      @app.before_request
      def before_request():
          if current_user.is_authenticated:
              current_user.last_seen = datetime.utcnow()
              db.session.commit()

  - 위 예에서 `db.session.add()`\ 가 생략됐는데, `current_user`\ 에서 Flask-Login이
    user loader 콜백함수를 실행해 DB세션에 반영하기 때문이다. `add`\ 를 해도 되는데, 생략해도 된다.

- 사용자가 프로필 수정하기

  - app/forms.py: Profile editor form::

      from wtforms import StringField, TextAreaField, SubmitField
      from wtforms.validators import DataRequired, Length

      # ...

      # 프로필 수정용으로 새로운 form 생성
      class EditProfileForm(FlaskForm):
          username = StringField('Username', validators=[DataRequired()])
          about_me = TextAreaField('About me', validators=[Length(min=0, max=140)])
          submit = SubmitField('Submit')

  - app/templates/edit_profile.html: Profile editor form::

      {% extends "base.html" %}

      {% block content %}
          <h1>Edit Profile</h1>
          <form action="" method="post">
              {{ form.hidden_tag() }}
              <p>
                  {{ form.username.label }}<br>
                  {{ form.username(size=32) }}<br>
                  {% for error in form.username.errors %}
                  <span style="color: red;">[{{ error }}]</span>
                  {% endfor %}
              </p>
              <p>
                  {{ form.about_me.label }}<br>
                  {{ form.about_me(cols=50, rows=4) }}<br>
                  {% for error in form.about_me.errors %}
                  <span style="color: red;">[{{ error }}]</span>
                  {% endfor %}
              </p>
              <p>{{ form.submit() }}</p>
          </form>
      {% endblock %}

  - app/routes.py: Edit profile view function::

      from app.forms import EditProfileForm

      @app.route('/edit_profile', methods=['GET', 'POST'])
      @login_required
      def edit_profile():
          form = EditProfileForm()
          # form에서 입력한 데이터가 validate_on_submit에서 True면 form에 있는 데이터를 current_user의 정보에 입력
          if form.validate_on_submit():
              current_user.username = form.username.data
              current_user.about_me = form.about_me.data
              db.session.commit()
              flash('Your changes have been saved.')
              return redirect(url_for('edit_profile'))
          # 정보를 보내는 것 없이 get 방식으로 페이지를 불러오면(request.method 함수로 어떤 방식인지 알 수 있음.)
          # form에 현재 정보만 미리 넣어줌.
          elif request.method == 'GET':
              form.username.data = current_user.username
              form.about_me.data = current_user.about_me
          return render_template('edit_profile.html', title='Edit Profile',
                                 form=form)

  - app/templates/user.html: Edit profile link::

        <!-- 프로필 수정 링크 추가. 본인프로필을 볼 때만 수정할 수 있는 버튼이 생성됨. -->
        {% if user == current_user %}
        <p><a href="{{ url_for('edit_profile') }}">Edit your profile</a></p>
        {% endif %}

Chapter 7: Error Handling
==========================================

- 플라스크에서 에러 다루기

  - stack trace를 살펴보면 어떤 에러가 발생했는지 알 수 있다.

  - 왜 에러가 발생했는지 등의 정보는 내부적으로만 보여져야 한다.

- 디버그 모드

  - 개발 단계에서는 바로 에러를 확인하고 싶을 때 디버그 모드를 사용한다. 브라우저 상에서 디버거를 볼 수 있다.

  - 프로덕션 서버에서는 절대 디버그모드가 켜져 있으면 안된다.

  - 터미널에서 `export FLASK_DEBUG=1`\ 을 통해 설정해준다. (윈도우에서는 `export` 대신 `set` 사용)

    - 디버그 모드를 끄고 싶다 `export FLASK_DEBUG=0`

- 사용자에게 보여줄 에러 페이지 만들기

  - `@errorhandler` 사용하기. `errors.py` 파일 추가

  - app/errors.py: Custom error handlers::

      from flask import render_template
      from app import app, db

      @app.errorhandler(404)
      def not_found_error(error):
          return render_template('404.html'), 404

      @app.errorhandler(500)
      def internal_error(error):
          db.session.rollback()
          return render_template('500.html'), 500

  - template에도 `404.html`, `500.html` 추가

    - app/templates/404.html: Not found error template::

        {% extends "base.html" %}

        {% block content %}
            <h1>File Not Found</h1>
            <p><a href="{{ url_for('index') }}">Back</a></p>
        {% endblock %}

    - app/templates/500.html: Internal server error template::

        {% extends "base.html" %}

        {% block content %}
            <h1>An unexpected error has occurred</h1>
            <p>The administrator has been notified. Sorry for the inconvenience!</p>
            <p><a href="{{ url_for('index') }}">Back</a></p>
        {% endblock %}

  - `__init__.py` 파일에도 errors 사용할 거라고 알려줌.

    - app/__init__.py: Import error handlers::

        # ...

        from app import routes, models, errors

- 에러 발생 시 이메일로 받기

  - 프로덕션 단계에서 에러가 발생하면 알아내기 힘듦.

  - 따라서, 에러 발생 시 stack trace를 포함한 메일을 받도록 구현.

  - `config.py` 파일에 이메일 정보 설정

  - flask는 파이썬의 `logging` 패키지를 사용

    - 패키지는 로그를 이메일로 보내는 기능을 포함하고 있음.

    - SMTPHandler 인스턴스를 flask logger 객체에 추가.

  - 디버그 모드가 아닐 때만 이메일을 받도록 설정 가능.

- 로그 기록을 파일로 만들기

  - `RotatingFileHandler` 클래스 생성

  - app/__init__.py: Email configuration::

      # ...
      from logging.handlers import RotatingFileHandler
      import os

      # ...

      if not app.debug:
          # ...

          if not os.path.exists('logs'):
              os.mkdir('logs')
          file_handler = RotatingFileHandler('logs/eblog.log', maxBytes=10240,
                                             backupCount=10)
          file_handler.setFormatter(logging.Formatter(
              '%(asctime)s %(levelname)s: %(message)s [in %(pathname)s:%(lineno)d]'))
          file_handler.setLevel(logging.INFO)
          app.logger.addHandler(file_handler)

          app.logger.setLevel(logging.INFO)
          app.logger.info('eblog startup')

  - `eblog.log`\ 라는 이름으로 `logs` 디렉토리에 로그 기록.

  - `RotatingFileHandler` 클래스: 일정한 크기를 유지하면서 로그를 기록한다.
    일정 크기를 넘어가면 오래된 로그는 지워진다.

  - `logging.Formatter` 클래스는 로그 메시지를 원하는대로 포매팅할 수 있게 해준다.

  - 위의 예에서는 로그 레벨을 `INFO`\ 까지 내렸다.

- 중복 유저 버그 고치기

  - 사용자 등록 시에는 `RegistrationForm`\ 에서 중복되는 username인지 판별함.

  - 프로필 변경 시에도 `EditProfileForm`\ 에 중복 사용자가 생기지 않도록 적용해줘야 함.

    - 사용자 등록 시와 다른 점이 있음. (아래 코드 주석으로 확인)

  - app/forms.py: Validate username in edit profile form.::

      class EditProfileForm(FlaskForm):
        username = StringField('Username', validators=[DataRequired()])
        about_me = TextAreaField('About me', validators=[Length(min=0, max=140)])
        submit = SubmitField('Submit')

        # 이름 변경 시에 이미 있는 이름이면 유효하지 않음.
        # 단, 본인 이름을 변경하지 않고 그대로 놔둔다면 이미 있는 username이지만, 해당 유저에게 할당된 것이므로 유효하다고 봐야함.
        def __init__(self, original_username, *args, **kwargs):
            super(EditProfileForm, self).__init__(*args, **kwargs)
            self.original_username = original_username

        def validate_username(self, username):
            if username.data != self.original_username:
                user = User.query.filter_by(username=self.username.data).first()
                if user is None:
                    raise ValidationError('다른 username을 사용하세요.')

  - app/routes.py: Validate username in edit profile form.::

      @app.route('/edit_profile', methods=['GET', 'POST'])
      @login_required
      def edit_profile():
          form = EditProfileForm(current_user.username)
          # ...

  - `EditProfileForm`\ 에 현재 username을 인수로 넣어줌.
    -> `form.py`에 `__init__` 함수가 정의돼있음.


Chapter 8: Followers
======================================

- 데이터베이스 관계

  - One-to-many

  - Many-to-Many

  - Many-to-One / One-to-One

- 팔로워 나타내기

  - 팔로워는 many-to-many 관계가 알맞다.

  - 단, user가 user와 연결되는 many-to-many 관계다. 즉, `self-referential` 관계

DB 모델
------------------------

- app/models.py: Followers association table::

    followers = db.Table('followers',
        db.Column('follower_id', db.Integer, db.ForeignKey('user.id')),
        db.Column('followed_id', db.Integer, db.ForeignKey('user.id'))
    )

- 모델 클래스와 상관없이 독립적으로 followers 테이블 생성

- User 클래스에 내가 팔로우한 유저(followed user)에 대한 정보를 생성해줘야 한다.

- app/models.py: Many-to-many followers relationship(유저테이블에 many-to-many 관계 생성)::

    class User(UserMixin, db.Model):
        # ...
        followed = db.relationship(
            'User', secondary=followers,
            primaryjoin=(followers.c.follower_id == id),
            secondaryjoin=(followers.c.followed_id == id),
            backref=db.backref('followers', lazy='dynamic'), lazy='dynamic')

- the left side user(`followed`) is following the right side user.

- 위에서 사용된 `db.relationship()`\ 의 인수를 알아보자.

  - `'User'`: 우측 entity. 이 예에서는 좌우 entity가 동일하다.

  - `secondary`: 관련 테이블 설정.

  - `primaryjoin`: 좌측 entity와(follower)의 조인컨디션 지정(follower 테이블의 follower_id 컬럼)

  - `secondaryjoin`: 우측 entity와(followed)의 조인컨디션 지정(follower 테이블의 followed_id 컬럼)

  - `backref`: 우측 entity에서 어떻게 관계에 엑세스 할 것인지 정의.

    - `lazy`: 실행 모드를 지정. `dynamic` 모드는 특정 요청이 있기 전까지는 실행하지 않는다.

- 터미널에서 DB 마이그레이션 실행

  - `flask db migrate -m "followers"`

  - `flask db upgrade`

- 다른 유저를 팔로우한 유저는 `followed` 관계에 리스트처럼 기록됨.

  - `user1`, `user2`\ 가 있을 때, (파이썬 코드)

    - `user1`\ 이 `user2`\ 를 팔로하게 만들기::

        user1.followed.append(user2)

    - 언팔로우하게 만들기::

        user1.followed.remove(user2)

- follow, unfollow 함수를 User 모델에서 미리 만들어놓는 게 좋음.

  - app/models.py: Add and remove followers::

      class User(UserMixin, db.Model):
          #...

          # follow, unfollow 함수를 User 모델에서 미리 만들어놓음.
          def follow(self, user):
              if not self.is_following(user):
                  self.followed.append(user)

          def unfollow(self, user):
              if self.is_following(user):
                  self.followed.remove(user)

          # 팔로잉 하고 있는지 DB에서 확인
          def is_following(self, user):
              return self.followed.filter(
                  followers.c.followed_id == user.id).count() > 0

  - `is_following` 함수도 만듦: 이미 팔로했는지 아닌지를 판별


팔로우한 유저(followed users)의 포스트 타임라인으로 받아보기
------------------------------------------------------------------

- `user.followed.all()`\ 를 이용하면 모든 followed 유저를 가져올 수 있다.

  - 좋지 않은 방법. 문제1) followed 유저가 수천만이면 수천 데이터베이스 쿼리를 날리고, 그 리스트를 merge 해야함.

  - 문제2) 페이징 시에 보통 가장 최근 포스트를 맨 앞에 가져오게 되는데,
    followed가 많으면 모든 포스트를 모아서 날짜순으로 정렬하지 않는 한, 어떤 포스트가 최근인지 알 수 없음.

- 좋은 방법: `app/models.py`: Followed posts query::

    class User(db.Model):
        #...
        def followed_posts(self):
            return Post.query.join(
                followers, (followers.c.followed_id == Post.user_id)
            ).filter(
                followers.c.follower_id == self.id
            ).order_by(
                Post.timestamp.desc()
            )

- join, filter, order_by 사용

  - 포스트와 followers 정보를 join 함

  - follower_id가 해당 유저인 정보만 가져옴. -> follower_id가 해당 유저인 포스트만 가져오는 셈.

  - order_by: 작성된 시간 순으로 정렬

- 내가 쓴 글도 타임라인에 포함시키기

- 두가지 방법: 1) followed에 자기자신 포함시키기. - 다른 상태에도 영향을 준다(followed 수가 한명 많아진다.)

- 2) User의 포스트를 가져오는 쿼리를 만들고, "union" 오퍼레이터 사용해서 하나로 만들어줌.

  - app/models.py: Followed posts query with user's own posts.::

      def followed_posts(self):
          followed = Post.query.join(
              followers, (followers.c.followed_id == Post.user_id)).filter(
                  followers.c.follower_id == self.id)
          own = Post.query.filter_by(user_id=self.id)
          return followed.union(own).order_by(Post.timestamp.desc())

함수 테스트 하기Unit testing: 파이썬에서 제공하는 `unittest` 패키지 사용
-------------------------------------------------------------------------

- `파이썬의 유닛테스트 패키지 사용법 <http://pythonstudy.xyz/python/article/21-%EC%9C%A0%EB%8B%9B-%ED%85%8C%EC%8A%A4%ED%8A%B8>`_

- 아래 테스트 파일(`tests.py`)을 만들어놓고, User 모델이 변경될 때마다 사용하면 됨.

- tests.py: User model unit tests.::

    from datetime import datetime, timedelta
    import unittest
    from app import app, db
    from app.models import User, Post

    class UserModelCase(unittest.TestCase):
        """User 모델을 테스트하는 클래스
        """

        # 테스트 사전처리 - setUp: 테스트 할 db 생성. 임시로 sqlite DBMS 사용
        def setUp(self):
            app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite://'
            db.create_all()

        # 테스트 사후처리 - tearDown: 테스트 한 db 삭제
        def tearDown(self):
            db.session.remove()
            db.drop_all()

        # 아래는 4개 함수에 대한 테스트
       def test_password_hashing(self):
            u = User(username='susan')
            u.set_password('cat')
            self.assertFalse(u.check_password('dog'))
            self.assertTrue(u.check_password('cat'))

        def test_avatar(self):
            # 본 예제에서는 아바타 기능을 사용하지 않았으므로 pass
            pass

        def test_follow(self):
            # 두명의 유저 생성. u1(john), u2(susan)
            u1 = User(username='john', email='john@example.com')
            u2 = User(username='susan', email='susan@example.com')
            db.session.add(u1)
            db.session.add(u2)
            db.session.commit()
            self.assertEqual(u1.followed.all(), [])
            self.assertEqual(u1.followers.all(), [])

            # u1이 u2를 follow 하게 만들기
            u1.follow(u2)
            db.session.commit()
            # u1이 u2를 팔로우하고 있는지 관련 내용 확인
            self.assertTrue(u1.is_following(u2))
            self.assertEqual(u1.followed.count(), 1)
            self.assertEqual(u1.followed.first().username, 'susan')
            self.assertEqual(u2.followers.count(), 1)
            self.assertEqual(u2.followers.first().username, 'john')

            u1.unfollow(u2)
            db.session.commit()
            self.assertFalse(u1.is_following(u2))
            self.assertEqual(u1.followed.count(), 0)
            self.assertEqual(u2.followers.count(), 0)

        def test_followed_posts(self):
            # 유저 4명 생성
            u1 = User(username='john', email='john@example.com')
            u2 = User(username='susan', email='susan@example.com')
            u3 = User(username='mary', email='mary@example.com')
            u4 = User(username='david', email='david@example.com')
            db.session.add_all([u1, u2, u3, u4])

            # 포스트 4개 생성
            now = datetime.utcnow()
            p1 = Post(body="post from john", author=u1,
                      timestamp=now + timedelta(seconds=1))
            p2 = Post(body="post from susan", author=u2,
                      timestamp=now + timedelta(seconds=4))
            p3 = Post(body="post from mary", author=u3,
                      timestamp=now + timedelta(seconds=3))
            p4 = Post(body="post from david", author=u4,
                      timestamp=now + timedelta(seconds=2))
            db.session.add_all([p1, p2, p3, p4])
            db.session.commit()

            # follower 관계 설정
            u1.follow(u2) # u1 follow u2
            u1.follow(u4) # u1 follow u4
            u2.follow(u3) # u2 follow u3
            u3.follow(u4) # u3 follow u4
            db.session.commit()

            # check the followed posts of each user
            f1 = u1.followed_posts().all()
            f2 = u2.followed_posts().all()
            f3 = u3.followed_posts().all()
            f4 = u4.followed_posts().all()
            self.assertEqual(f1, [p2, p4, p1])
            self.assertEqual(f2, [p2, p3])
            self.assertEqual(f3, [p3, p4])
            self.assertEqual(f4, [p4])

    # unittest 실행
    if __name__ == '__main__':
        unittest.main(verbosity=2)

어플리케이션에 follow 기능 반영하기
------------------------------------------

- app/routes.py: Follow and unfollow routes.::

    @app.route('/follow/<username>')
    @login_required
    def follow(username):
        user = User.query.filter_by(username=username).first()
        if user is None:
            flash('User {} not found.'.format(username))
            return redirect(url_for('index'))
        if user == current_user:
            flash('You cannot follow yourself!')
            return redirect(url_for('user', username=username))
        current_user.follow(user)
        db.session.commit()
        flash('You are following {}!'.format(username))
        return redirect(url_for('user', username=username))

    @app.route('/unfollow/<username>')
    @login_required
    def unfollow(username):
        user = User.query.filter_by(username=username).first()
        if user is None:
            flash('User {} not found.'.format(username))
            return redirect(url_for('index'))
        if user == current_user:
            flash('You cannot unfollow yourself!')
            return redirect(url_for('user', username=username))
        current_user.unfollow(user)
        db.session.commit()
        flash('You are not following {}.'.format(username))
        return redirect(url_for('user', username=username))

- app/templates/user.html: Follow and unfollow links in user profile page.::

      ...
      <h1>User: {{ user.username }}</h1>
      {% if user.about_me %}<p>{{ user.about_me }}</p>{% endif %}
      {% if user.last_seen %}<p>Last seen on: {{ user.last_seen }}</p>{% endif %}
      <p>{{ user.followers.count() }} followers, {{ user.followed.count() }} following.</p>
      {% if user == current_user %}
      <p><a href="{{ url_for('edit_profile') }}">Edit your profile</a></p>
      {% elif not current_user.is_following(user) %}
      <p><a href="{{ url_for('follow', username=user.username) }}">Follow</a></p>
      {% else %}
      <p><a href="{{ url_for('unfollow', username=user.username) }}">Unfollow</a></p>
      {% endif %}
      ...


Chapter 9: Pagination
===============================

포스트 작성하기
--------------------------

- 포스트를 입력할 수 있는 Form 생성

  - app/forms.py: Blog submission form.::

      class PostForm(FlaskForm):
          post = TextAreaField('Say something', validators=[
              DataRequired(), Length(min=1, max=140)])
          submit = SubmitField('Submit')

- index 템플릿에 포스트 form 관련 내용 추가

  - app/templates/index.html: Post submission form in index template::

      {% extends "base.html" %}

      {% block content %}
          <h1>Hi, {{ current_user.username }}!</h1>
          <form action="" method="post">
              {{ form.hidden_tag() }}
              <p>
                  {{ form.post.label }}<br>
                  {{ form.post(cols=32, rows=4) }}<br>
                  {% for error in form.post.errors %}
                  <span style="color: red;">[{{ error }}]</span>
                  {% endfor %}
              </p>
              <p>{{ form.submit() }}</p>
          </form>
          {% for post in posts %}
          <p>
          {{ post.author.username }} says: <b>{{ post.body }}</b>
          </p>
          {% endfor %}
      {% endblock %}

- view 함수 추가

  - app/routes.py: Post submission form in index view function.::

      from app.forms import PostForm
      from app.models import Post

      # get 방식뿐만 아니라 post 방식도 받을 수 있도록 설정
      @app.route('/', methods=['GET', 'POST'])
      @app.route('/index', methods=['GET', 'POST'])
      @login_required
      def index():
          form = PostForm()
          if form.validate_on_submit():
              post = Post(body=form.post.data, author=current_user)
              db.session.add(post)
              db.session.commit()
              flash('Your post is now live!')
              # 포스트가 제대로 입력됐으면 index 페이지로 redirect
              return redirect(url_for('index'))
          # followed_posts 함수를 이용해서 current_user의 팔로우 및 본인 글을 불러옴.
          posts = current_user.followed_posts().all()
          return render_template("index.html", title='Home Page', form=form,
                                 posts=posts)

  - `Post/Redirect/Get` 패턴: post 요청이 redirect를 통해서 되면, 자동으로 get방식으로 인식된다.

    - Form이 중복으로 입력되는 것을 막아줌.

Follow할 User 쉽게 찾기
---------------------------

- 다른 유저를 찾기 위한 "Explore" 페이지 생성. 모든 유저의 포스트를 보여주는 페이지

  - app/routes.py: Explore view function.::

      @app.route('/explore')
      @login_required
      def explore():
          # 모든 포스트를 가져옴.
          posts = Post.query.order_by(Post.timestamp.desc()).all()
          # index.html 페이지 사용
          return render_template('index.html', title='Explore', posts=posts)

  - `render_template()`\ 에서 `index.html`\ 을 사용

- app/templates/base.html: 네비게이션바에 Explore 페이지로 가는 링크 추가::

        <a href="{{ url_for('explore') }}">Explore</a>

- app/templates/_post.html: 포스트 템플릿에 나오는 username을 링크로 표시하도록 변경::

    <table>
        <tr valign="top">
            <td><img src="{{ post.author.avatar(36) }}"></td>
            <td>
                <a href="{{ url_for('user', username=post.author.username) }}">
                    {{ post.author.username }}
                </a>
                says:<br>{{ post.body }}
            </td>
        </tr>
    </table>

- app/templates/index.html: _post.html을 index 페이지에 사용::

    ...
    {% for post in posts %}
        {% include '_post.html' %}
    {% endfor %}
    ...

Pagination - 페이지 이동 링크(버튼) 만들기
---------------------------------------------------

- Flask-SQLAlchemy는 `paginate()` 메서드 제공.

  - 3개의 인수: 1) page number

  - 2) 페이지당 아이템 수

  - 3) error flag: `True`\ 면 out of range page일 때 404 에러를 반환.
       `False`\ 면 빈 리스트 반환

- config 파일에서 포스트당 페이지를 정할 수 있음.

  - config.py: Posts per page configuration.::

      class Config(object):
          # ...
          POSTS_PER_PAGE = 3

- URL에서 query string argument를 받을 수 있음

  - URL에서 `?` 뒤에 있는 것이 query string argument

  - query string argument는 `request.args` 객체로 받을 수 있음.

  - 이 예에서는 인수명을 **page**\ 로 받음.

- `paginate`\ 는 페이지 네비게이션에 사용되는 attribute 몇을 가지고 있다.

  - `has_next`: `True` = 현재 페이지에서 다음 페이지가 있을 때

  - `has_prev`: `True` = 현재 페이지에서 이전 페이지가 있을 때

  - `next_num`: 다음 페이지 number

  - `prev_num`: 이전 페이지 number

- view file에 적용

  - app/routes.py: Next and previous page links.::

      @app.route('/', methods=['GET', 'POST'])
      @app.route('/index', methods=['GET', 'POST'])
      @login_required
      def index():
          # ...
          page = request.args.get('page', 1, type=int)
          posts = current_user.followed_posts().paginate(
              page, app.config['POSTS_PER_PAGE'], False)
              # 페이지당 포스트 수를 app.config의 POST_PER_PAGE에서 가져옴.
          # 현재 posts가 다음 페이지가 있으면= has_next가 True면 url_for에 index와 page number를 인수로 넘겨줌
          next_url = url_for('index', page=posts.next_num) \
              if posts.has_next else None
          # next_url과 같은 로직
          prev_url = url_for('index', page=posts.prev_num) \
              if posts.has_prev else None
          return render_template('index.html', title='Home', form=form,
                                 posts=posts.items, next_url=next_url,
                                 prev_url=prev_url)

       @app.route('/explore')
       @login_required
       def explore():
          page = request.args.get('page', 1, type=int)
          posts = Post.query.order_by(Post.timestamp.desc()).paginate(
              page, app.config['POSTS_PER_PAGE'], False)
          next_url = url_for('explore', page=posts.next_num) \
              if posts.has_next else None
          prev_url = url_for('explore', page=posts.prev_num) \
              if posts.has_prev else None
          return render_template("index.html", title='Explore', posts=posts.items,
                                next_url=next_url, prev_url=prev_url)

- template에 적용

  - app/templates/index.html: Render pagination links on the template.::

      ...
      {% for post in posts %}
          {% include '_post.html' %}
      {% endfor %}
      {% if prev_url %}
      <a href="{{ prev_url }}">Newer posts</a>
      {% endif %}
      {% if next_url %}
      <a href="{{ next_url }}">Older posts</a>
      {% endif %}
      ...

- 프로필 페이지에 pagination 적용

  - app/routes.py: Pagination in the user profile view function.::

      @app.route('/user/<username>')
      @login_required
      def user(username):
          user = User.query.filter_by(username=username).first_or_404()
          page = request.args.get('page', 1, type=int)
          posts = user.posts.order_by(Post.timestamp.desc()).paginate(
              page, app.config['POSTS_PER_PAGE'], False)
          next_url = url_for('user', username=user.username, page=posts.next_num) \
              if posts.has_next else None
          prev_url = url_for('user', username=user.username, page=posts.prev_num) \
              if posts.has_prev else None
          return render_template('user.html', user=user, posts=posts.items,
                                 next_url=next_url, prev_url=prev_url)

  - app/templates/user.html: Pagination links in the user profile template.::

      ...
      {% for post in posts %}
          {% include '_post.html' %}
      {% endfor %}
      {% if prev_url %}
      <a href="{{ prev_url }}">Newer posts</a>
      {% endif %}
      {% if next_url %}
      <a href="{{ next_url }}">Older posts</a>
      {% endif %}


Chapter 10: Email Support
===================================

- 패스워드를 잊어버렸을 때, 리셋을 위해서 이메일을 사용한다.

- `Flask-Mail <https://pythonhosted.org/Flask-Mail/>`_: 메일을 보내기 위한 extension

- `JSON Web Tokens <https://jwt.io/>`_: 보안 토큰 생성. 패스워드 리셋 링크에 사용.

- `__init__.py`\ 에 메일 인스턴스 생성

  - app/__init__.py: Flask-Mail instance.::

      # ...
      from flask_mail import Mail

      app = Flask(__name__)
      # ...
      mail = Mail(app)

- 메일을 보내는 방법 두가지

  1) 가상 email 서버 생성

    - 터미널에서 실행, 아래 2줄은 환경변수 설정::

      (venv) $ python -m smtpd -n -c DebuggingServer localhost:8025
      (venv) $ export MAIL_SERVER=localhost
      (venv) $ export MAIL_PORT=8025

  2) 실제 email 서버 사용

    - 터미널에서 아래처럼 환경변수 설정::

        (venv) $ export MAIL_SERVER=smtp.googlemail.com
        (venv) $ export MAIL_PORT=587
        (venv) $ export MAIL_USE_TLS=1
        (venv) $ export MAIL_USERNAME=<your-gmail-username>
        (venv) $ export MAIL_PASSWORD=<your-gmail-password>

    - Gmail은 "less secure apps" 설정 필요할 수도 있음.


Chapter 11: Facelift
===================================

- 부트스트랩 사용하기


Chapter 12: Dates and Times
==================================

- 나라마다 시간대를 맞추는 문제

- 위치에 따라 `datetime.now()`\ 가 출력하는 결과가 다르다.

- UTC 기준으로 항상 같은 값을 출력하는 `datetime.utcnow()`\ 를 사용하는 것이 좋다.

- Timezone 문제를 다루는 방식

  - 예전 방식: 서버가 클라이언트의 정보를 받아서 계산해서 클라이언트에게 넘겨줌.

  - 현재 방식: 서버는 항상 같은 값을 주고, 클라이언트에서 자바스크립트를 이용해서 로컬 시간으로 변경

Moment.js와 Flask-Moment 사용하기
----------------------------------------------

- Moment.js는 날짜와 시간을 렌더링하는 자바스크립트 라이브러리

- flask-moment를 사용하면 자바스크립트를 직접사용하지 않아도 템플릿 상에서 날짜에 대한 조절을 할 수 있다.

- 설치: `$ pip install flask-moment`

- app/__init__.py: Flask-Moment instance.::

# ...
from flask_moment import Moment

app = Flask(__name__)
# ...
moment = Moment(app)

- 템플릿에 moment.js 추가 app/templates/base.html: Including moment.js in the base template.::

    ...

    {% block scripts %}
        {{ super() }}
        {{ moment.include_moment() }}
    {% endblock %}

  - `moment.include_moment()`\ 는 `<script>` 태그를 만든다.

- `moment(시간).함수(형식)`: 시간이 지정한 형식대로 나온다.

  - 시간은 ISO 8601 표준 포맷으로 입력. `{{ year }}-{{ month }}-{{ day }}T{{ hour }}:{{ minute }}:{{ second }}{{ timezone }}`

  - 예::

      moment('2017-09-28T21:45:23Z').format('L')
      "09/28/2017"
      moment('2017-09-28T21:45:23Z').format('LL')
      "September 28, 2017"
      moment('2017-09-28T21:45:23Z').format('LLL')
      "September 28, 2017 2:45 PM"
      moment('2017-09-28T21:45:23Z').format('LLLL')
      "Thursday, September 28, 2017 2:45 PM"
      moment('2017-09-28T21:45:23Z').format('dddd')
      "Thursday"
      moment('2017-09-28T21:45:23Z').fromNow()
      "7 hours ago"
      moment('2017-09-28T21:45:23Z').calendar()
      "Today at 2:45 PM"

- app/templates/user.html: Render timestamp with moment.js.::

    {% if user.last_seen %}
    <p>Last seen on: {{ moment(user.last_seen).format('LLL') }}</p>
    {% endif %}

- `moment()`\ 는 `datetime` 객체.

- `fromNow()`\ 로 timestamp 렌더링 가능.

  - app/templates/_post.html: Render timestamp in post sub-template.::

      <a href="{{ url_for('user', username=post.author.username) }}">
          {{ post.author.username }}
      </a>
      said {{ moment(post.timestamp).fromNow() }}:
      <br>
      {{ post.body }


Chapter 13: I18n and L10n
==================================


- 번역에는 `Flask-Babel` 사용

- Babel 클래스 인스턴스 생성 app/__init__.py: Flask-Babel instance.::

    # ...
    from flask_babel import Babel

    app = Flask(__name__)
    # ...
    babel = Babel(app)

- 지원하는 언어 리스트 설정 config.py: Supported languages list.::

    class Config(object):
        # ...
        LANGUAGES = ['en', 'es']

- `Babel`\ 이 지원하는 `localeselector` 데코레이터 사용

  - app/__init__.py: Select best language.::

      from flask import request

      # ...

      @babel.localeselector
      def get_locale():
          return request.accept_languages.best_match(app.config['LANGUAGES'])
          # 특정언어로 고정시키고 싶으면 return 'ko' 이런식으로 설정

  - `request` 객체의 accept_languages 속성: 클라이언트가 request에 보내는 헤더 정보중 언어 정보.


- `messages.po`, `messages.mo`, `messages.pot` 파일.

  - 터미널에서 다음과 같이 실행::

    $ pybabel extract -F babel.cfg -k _l -o messages.pot .
    $ pybabel update -i messages.pot -d app/translations

- 날짜와 시간 번역하기

  - `get_locale()` 함수: 선택된 언어와 지역을 get_locale 함수를 통해 반환한다.

  - `g` 객체에 이 정보 보내기

  - app/routes.py: Store selected language in flask.g. ::

      # ...
      from flask import g
      from flask_babel import get_locale

      # ...

      @app.before_request
      def before_request():
          # ...
          g.locale = str(get_locale())

  - moment.js에서 위 속성에 접근하기

  - app/templates/base.html: Set locale for moment.js.::

      ...
      {% block scripts %}
          {{ super() }}
          {{ moment.include_moment() }}
          {{ moment.lang(g.locale) }}
      {% endblock %}

- 코맨드 라인에서 번역 기능 사용하기


Chapter 14: Ajax
============================

- 어플리케이션 모델에 대해

  - 전통적인 server-side 모델에서는 HTTP request를 받으면, 클라이언트가 웹 어플리케이션을 사용하는 동안
    서버가 계속 작동하면서 그 요청에 대한 답을 한다.

  - 클라이언트 측에서 작업을 하는 client-side 모델도 있다. request를 통해 html과 함께 코드(보통은 자바스크립트)를 받는다.
    html 부분은 먼저 디스플레이하고, 코드를 실행한다.

    - 엄격한 client-side 어플리케이션은 최초에 한번만 서버에서 request를 통해 데이터를 가져온다.
      이런 타입을 'Single Page Applications'(혹은 SPAs)라고 한다.

  - 대부분의 어플리케이션은 위 두 모델의 하이브리드 형태다.

- Ajax(Asynchronous JavaScript and XML)

  - 포스트 실시간 번역을 예로 들면, 클라이언트의 브라우저는 포스트에 대한 데이터를
    asynchronous requests를 통해 서버로 전송하고,
    서버는 그 데이터에 대해 별도의 페이지 새로고침 없이 번역작업을 해서 repond 한다.
    클라이언트는 번역된 결과를 현재 페이지에 동적으로(dynamically) 입력한다.

실시간 번역 적용하기
--------------------------

  - Ajax 서비스를 이용하기 적절한 예. 한 포스트를 번역하기 위해 모든 다른 블로그 포스트를 새로고침하는 것보다
    해당 부분의 번역만 원본 텍스트 밑에 덧붙여지도록 하는 것이 훨씬 낫다.

  - 적용 단계

    - 번역할 원본 텍스트가 어떤 언어인지, 어떤 언어로 번역돼야 할지 파악

    - Ajax 요청을 서버로 보내고 서버에서 번역 API에 연결

    - 서버에서 번역된 텍스트와 함께 reponse를 보내면 클라이언트 측 자바스크립트 코드가 페이지에 동적으로 텍스트 넣기

- 원본 텍스트 언어 알아내기

  - 파이썬의 언어를 알아내는 `guess_language` 라이브러리 사용.

    - 원래 파이썬2에만 사용 가능하지만, 3에서도 사용가능하게 설치::

      (venv) $ pip install guess-language_spirit

  - `Post` 모델에 `language` 필드 추가

    - app/models.py: Add detected language to Post model.::

        class Post(db.Model):
            # ...
            language = db.Column(db.String(5))

    - 모델을 변경했으니, alembic을 통해 migration 다시 실행, migrate&upgrade

  - app/routes.py: Save language for new posts.::

      from guess_language import guess_language

      @app.route('/', methods=['GET', 'POST'])
      @app.route('/index', methods=['GET', 'POST'])
      @login_required
      def index():
          form = PostForm()
          if form.validate_on_submit():
              # post 입력시에 해당 post가 어떤 언어인지를 db에 같이 입력.
              language = guess_language(form.post.data)
              if language == 'UNKNOWN' or len(language) > 5:
                  language = ''
              post = Post(body=form.post.data, author=current_user,
                          language=language)
              # ...

- "번역" 링크 추가하기

  - app/templates/_post.html: Add a translate link to posts.::

      {% if post.language and post.language != g.locale %}
      <br><br>
      <a href="#">{{ _('Translate') }}</a>
      {% endif %}

- 서드파티 번역 서비스

  - Google Cloud Translation API, Microsoft Translator Text API

    - 둘다 유료지만, MS는 짧은 문장은 무료로 사용 가능. -> 예에서는 MS API 사용

  - view file 만들기

    - app/translate.py: Text translation function.::

        import json
        import requests
        from flask_babel import _
        from app import app

        def translate(text, source_language, dest_language):
            if 'MS_TRANSLATOR_KEY' not in app.config or \
                    not app.config['MS_TRANSLATOR_KEY']:
                return _('Error: the translation service is not configured.')
            auth = {'Ocp-Apim-Subscription-Key': app.config['MS_TRANSLATOR_KEY']}
            r = requests.get('https://api.microsofttranslator.com/v2/Ajax.svc'
                             '/Translate?text={}&from={}&to={}'.format(
                                 text, source_language, dest_language),
                             headers=auth)
            if r.status_code != 200:
                return _('Error: the translation service failed.')
            return json.loads(r.content.decode('utf-8-sig'))

  - MS 번역 API는 HTTP requests를 받음. `requests` 패키지 사용.

    - 번역 API로 request 보내기

      - requests 패키지의 get() 메서드 사용: 첫번째 인수로 URL을 받아 GET 메서드 방식으로 HTTP 리퀘스트를 보냄.

        - 예에서 사용한 /v2/Ajax.svc/Translate URL은 번역 서비스의 endpoint로, 번역 데이터를 JSON형식으로 반환.
          query string arguments를 URL 안에 같이 받음.

            - query string arguments

              - `text`: 원본 텍스트

              - `from`: 원본 텍스트의 언어

              - `to`: 번역 완료 언어

      - `requests.get()`\ 은 서비스가 제공하는 모든 디테일을 담은 response 객체를 반환.

        - `status_code`\ 는 리퀘스트에 대한 상태. 200이면 정상적으로 리퀘스트에 대한 response가 온 것.
          200이 아니면 error를 반환하고, 200이면 response에 대한 json값을 반환.


- 서버에서의 Ajax

  - 사용자가 번역 링크를 누르면 포스트 아래에 번역 내용이 나타난다.

  - 비동기(of Ajax) 리퀘스트는 xml이나 json 같은 데이터만 반환한다.
    아래 번역 view 함수는 MS 번역 API를 불러오고, 번역된 텍스트를 json 포맷으로 반환한다.

  - app/routes.py: Text translation view function.::

      from flask import jsonify
      from app.translate import translate

      @app.route('/translate', methods=['POST'])
      @login_required
      def translate_text():
          return jsonify({'text': translate(request.form['text'],
                                            request.form['source_language'],
                                            request.form['dest_language'])})

  - `request.form` 속성은 제출할 때 보내지는 데이터의 정보가 담긴 딕셔너리다.
    이전에는 Flask-WTF를 사용하기 때문에 `request.form` \ 을 쓸 일이 없었지만,
    이 경우에는 web form이 없으므로 데이터에 직접 접근해야 한다.

  - 위에서 `jsonify()` 안에 `translate`\ 를 사용한다.

  - `jsonify()`\ 는 Flask의 함수로, 딕셔너리를 JSON의 형태로 바꿔준다.
    `jsonify()`의 반환값은 클라이언트에게 되돌려질 HTTP response다.

- 클라이언트에서의 Ajax

  - 번역 링크를 누르면 번역이 되도록 구현 필요. 자바스크립트가 브라우저에서 실행될 때, 페이지는 DOM을
    통해 내부적으로 보여진다. 이는 페이지에 있는 모든 요소를 참조하는 계층적인 구조다.
    컨텍스트 안에서 실행되는 자바스크립트 코드는 페이지의 변경을 위해 DOM을 변경할 수 있다.

  - 자바스크립트가 번역에 필요한 3개 인수를 얻기 위해 DOM에 노드를 위치시킨다.

    - 블로그 포스트를 포함하는 DOM 노드를 식별하는 것을 쉽게하기 위해 고유 ID를 붙여준다.
      `_post.html`\ 을 보면 {{ post.body }}가 있는데, 이걸 <span> 태그로 감싸고 id를 붙여준다.

  - app/templates/_post.html: Add an ID to each blog post.::

      <span id="post{{ post.id }}">{{ post.body }}</span>

    - 각 포스트마다 post1, post2와 같이 id를 붙여줬다. 모든 포스트마다 각각의 `post<id>` 노드를 갖게 됐다.

  - app/templates/_post.html: Add an ID to the translate link.::

      <span id="translation{{ post.id }}">
          <a href="#">{{ _('Translate') }}</a>
      </span>

    - 각 번역 링크에도 translation<id>로 식별 id를 넣어줌.

  - 다음 단계는 모든 번역 작업을 할 함수를 작성.

    - app/templates/base.html: Client-side translate function.::

        {% block scripts %}
            ...
            <script>
                function translate(sourceElem, destElem, sourceLang, destLang) {
                    $(destElem).html('<img src="{{ url_for('static', filename='loading.gif') }}">');
                    $.post('/translate', {
                        text: $(sourceElem).text(),
                        source_language: sourceLang,
                        dest_language: destLang
                    }).done(function(response) {
                        $(destElem).text(response['text'])
                    }).fail(function() {
                        $(destElem).text("{{ _('Error: Could not contact server.') }}");
                    });
                }
            </script>
        {% endblock %}

      - 앞의 두 개 인수는 포스트와 번역 링크에 대한 고유 ID고, 마지막 2개 인수는 원본과 목적 언어 코드다.

    - `$.post()`: jquery 함수. web form이 하는 방식과 비슷하게 데이터를 서버에 보냄.
      이렇게 보내면 `request.form` 딕셔너리로 사용할 수 있음.

      - `$.post()` 2개 인수

        1. 리퀘스트 보낼 URL

        2. 서버에 필요한 3개 데이터를 포함한 딕셔너리(자바스크립트식으로 표현하자면 객체)

    - 자바스크립트는 수많은 콜백함수(혹은 promises)와 함께 작동한다. 자바스크립트는 대기없이 모든 것을 비동기로 처리한다.
      따라서 response가 정상적으로 받아들여졌을 때, 브라우저가 불러올 콜백함수를 제공하는 것이 필요하다.
      에러가 발생했을 때와 그렇지 않을 때의 콜백함수를 모두 지정해주면, 좀 더 로버스트하고 모든 상황에 적용 가능하다.

      $.post(<url>, <data>).done(function(response) {
          // success callback
      }).fail(function() {
          // error callback
      })

    - `$.post()`\ 가 성공하면 done을, 실패하면 fail의 함수를 실행.

    - app/templates/_post.html: Translate link handler.::

          <span id="translation{{ post.id }}">
              <a href="javascript:translate(
                          '#post{{ post.id }}',
                          '#translation{{ post.id }}',
                          '{{ post.language }}',
                          '{{ g.locale }}');">{{ _('Translate') }}</a>
          </span>

    - `#`\ 를 이용해서 id를 인수로 넘겨줌.




참고
================

- `WSGI <https://ko.wikipedia.org/wiki/%EC%9B%B9_%EC%84%9C%EB%B2%84_%EA%B2%8C%EC%9D%B4%ED%8A%B8%EC%9B%A8%EC%9D%B4_%EC%9D%B8%ED%84%B0%ED%8E%98%EC%9D%B4%EC%8A%A4>`_

  - 웹 서버 게이트웨이 인터페이스(Web Server Gateway Interface)

  - 웹서버와 웹애플리케이션의 인터페이스를 위한 파이썬 프레임 워크

- 비동기(Asynchronous)

  - 보통 한 작업을 멈추지 않고, 다른 작업을 같이, 즉시, 바로 다음 진행할 수 있게 하는 경우에 비동기라는 말을 붙인다.

  - 비동기 입출력, 비동기 프로그래밍 등

- 서드파티

  - 하드웨어 생산자(퍼스트 파티), 생산자에게 승인을 받은 소프트웨어 생산자(세컨드 파티) 외의
    제3자가 만든 소프트웨어. 각 분야마다 뜻은 조금씩 다르지만, 전체적으로는 비슷한 느낌으로 사용.
