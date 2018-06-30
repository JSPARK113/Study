==========================
The Flask Mega Tutorial
==========================

.. Contents:: 목차


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

- `WWW SQL Designer<http://ondras.zarovi.cz/sql/demo/>`_: sql 스키마를 그릴 수 있다.

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

- `flask db upgrade`를 통해 DB에 Alembic 버전을 적용할 수 있다.

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

- `eblog.py` 파일에 코드 추가

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
          Microblog:
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
