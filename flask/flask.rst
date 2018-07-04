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

- DB 모델

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


- 팔로우한 유저(followed users)의 포스트 타임라인으로 받아보기

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

- Unit testing: 파이썬에서 제공하는 `unittest` 패키지 사용

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

- 어플리케이션에 follow 기능 반영하기

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
