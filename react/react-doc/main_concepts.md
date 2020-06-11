# Main Concepts

## 목차
1. [JSX](#JSX)
2. [엘리먼트 렌더링](#엘리먼트-렌더링)
3. [Components와 Props](#Components와-Props)
4. [State and Lifecycle](#State-and-Lifecycle)
5. [Handling Events](#Handling-Events)

## [JSX](https://ko.reactjs.org/docs/introducing-jsx.html)

- JSX는 React "element"를 생성한다.
- markup과 '기능'을 다른 파일로 분리하는 것 대신, component라고 하는 '관심사concern'단위로 파일을 나눈다.

### JSX에 표현식 포함하기: 중괄호 안에 표시
- 예제
  ```
  const name = 'Josh Perez';
  const element = <h1>Hello, {name}</h1>;

  ReactDOM.render(
  element,
  document.getElementById('root')
  );
  ```

### JSX 속성 정의
  - 속성은 `camelCase`로 정의: `tab-index`는 `tabIndex`로 표현
  - string literals로 정의: `const element = <div tabIndex="0"></div>;`
  - 표현식으로 정의(중괄호 안): `const element = <img src={user.avatarUrl}></img>;`

### JSX Prevents Injection Attacks
  - JSX는 모든 문장을 그냥 string으로 만들어버린다. -> 다른 스크립트가 실행되 생길 수 있는 문제cross-site-scripting(XSS) 방지

### JSX 객체 표현
  - Babel은 JSX를 `React.createElement()` 호출해 컴파일한다.
  - 아래 두 예제는 동일하다.
    ```
    const element = (
      <h1 className="greeting">
          Hello, world!
      </h1>
    );
    ```
    ```
    const element = React.createElement(
      'h1',
      {className: 'greeting'},
      'Hello, world!'
    );
    ```
  - `React.createElement()`는 버그가 없는 코드를 위해 몇가지 검사를 진행하며, 아래와 같은 객체를 생성한다.
    ```
    // Note: this structure is simplified
    const element = {
      type: 'h1',
      props: {
        className: 'greeting',
        children: 'Hello, world!'
      }
    };
    ```
  - 이런 객체가 `React Element`이며, 리액트는 이 객체를 읽어 DOM을 구축한다.

## [엘리먼트 렌더링](https://ko.reactjs.org/docs/rendering-elements.html)

- Element는 리액트 앱의 '가장 작은 단위'로, 화면에 표시할 내용을 기술한다.
- DOM Element와 달리, 리액트 element는 일반 객체다. React DOM은 리액트 element와 매칭되는 DOM을 업데이트한다.

### element를 DOM으로 렌더링하기
- HTML 파일에 있는 `<div id="root"></div>`는 root DOM이다.
  - 이 안에 들어가는 모든 엘리먼트를 React DOM에서 관리한다.
- 리액트 엘리먼트를 root DOM에 렌더링하려면 `ReactDOM.render()`로 전달하면 된다.

### 렌더링 된 엘리먼트 업데이트 하기
- 리액트 엘리먼트는 불변객체immutable object다. 엘리먼트는 한번 생성되면 변하지 않는다. 
- 즉, UI를 변경하기 위해 새 엘리먼트를 만드려면 `ReactDOM.render()`를 다시 실행해야 한다.
  - 예제: 
    ```
    function tick() {
      const element = (
        <div>
          <h1>Hello, world!</h1>
          <h2>It is {new Date().toLocaleTimeString()}.</h2>
        </div>
      );
      ReactDOM.render(
        element,
        document.getElementById('root')
      );
    }

    setInterval(tick, 1000);
    ```

### 변경된 부분만 업데이트
- React DOM은 해당 엘리먼트(+자식 엘리먼트)를 이전 엘리먼트와 비교하고, 필요한 경우에만 DOM을 업데이트한다.

## [Components와 Props](https://ko.reactjs.org/docs/components-and-props.html)
- 개념적으로 컴포넌트는 자바스크립트 함수와 같다. 
  - 임의의 인풋(props)를 받아 리액트 엘리먼트를 반환한다.

### Fuction과 Class 컴포넌트
- 함수 컴포넌트 예제: props를 받아 리액트 엘리먼트는 반환한다.
  ```
  function Welcome(props) {
    return <h1>Hello, {props.name}</h1>;
  }
  ```
- 클래스 컴포넌트 예제: ES6 class를 사용해서 컴포넌트를 정의한다.
  ```
  class Welcome extends React.Component {
    render() {
      return <h1>Hello, {this.props.name}</h1>;
    }
  }
  ```
- 함수형과 클래스형 컴포넌트의 차이점은 다음 섹션에서 살펴본다.

### 컴포넌트 렌더링
- 리액트 엘리먼트는 DOM 태그 외에도 사용자 정의 컴포넌트로 표현될 수 있다.
- 예제:
  ```
  function Welcome(props) {
    return <h1>Hello, {props.name}</h1>;
  }

  const element = <Welcome name="Sara" />;
  ReactDOM.render(
    element,
    document.getElementById('root')
  );
  ```
  1. `<Welcome name="Sara" />` 엘리먼트를 가지고 `ReactDOM.render()`를 호출한다.
  2. 리액트는 `{name: 'Sara'}` props를 가진 `Welcome` 컴포넌트를 호출한다.
  3. `Welcome` 컴포넌트는 `<h1>Hello, Sara</h1>`를 반환한다.
  4. React DOM은 `<h1>Hello, Sara</h1>`와 일치하도록 DOM을 효율적으로 업데이트한다.

- 참고: 컴포넌트 이름은 항상 대문자로 시작
  - React는 소문자로 시작하는 컴포넌트를 DOM 태그로 처리한다.

### 컴포넌트 합성 Composing Components
- 컴포넌트는 다른 컴포넌트를 포함해 결과를 return할 수 있다.
  ```
  function Welcome(props) {
    return <h1>Hello, {props.name}</h1>;
  }

  function App() {
    return (
      <div>
        <Welcome name="Sara" />
        <Welcome name="Cahal" />
        <Welcome name="Edite" />
      </div>
    );
  }
  ```

### 컴포넌트 추출 Extracting Components
- 예제: 아래 컴포넌트를 작은 단위로 쪼개보자
  ```
  function Comment(props) {
    return (
      <div className="Comment">
        <div className="UserInfo">
          <img className="Avatar"
            src={props.author.avatarUrl}
            alt={props.author.name}
          />
          <div className="UserInfo-name">
            {props.author.name}
          </div>
        </div>
        <div className="Comment-text">
          {props.text}
        </div>
        <div className="Comment-date">
          {formatDate(props.date)}
        </div>
      </div>
    );
  }
  ```

- 변경한 예제:
  ```
  // Avatar 컴포넌트
  function Avatar(props) {
    return (
      <img className="Avatar"
        src={props.user.avatarUrl}
        alt={props.user.name}
      />
    );
  }
  // UserInfo 컴포넌트(Avatar 컴포넌트 포함)
  function UserInfo(props) {
    return (
      <div className="UserInfo">
        <Avatar user={props.user} />
        <div className="UserInfo-name">
          {props.user.name}
        </div>
      </div>
    );
  }
  // UserInfo 컴포넌트를 반영한 수정컴포넌트
  function Comment(props) {
    return (
      <div className="Comment">
        <UserInfo user={props.author} />
        <div className="Comment-text">
          {props.text}
        </div>
        <div className="Comment-date">
          {formatDate(props.date)}
        </div>
      </div>
    );
  }
  ```

### Props are Read-Only
- `pure function` & `impure function`
  - 순수함수는 같은 입력에 대해 같은 출력이 나온다.
- (중요!) 모든 리액트 컴포넌트는 props에 대해 순수함수로 작동한다.


## [State and Lifecycle](https://ko.reactjs.org/docs/state-and-lifecycle.html)
- `state`는 `props`와 유사하지만, private하며 컴포넌트에 의해 완전히 제어fully controlled 된다.
- 이 섹션에서는 시계 예제를 state를 이용해 고쳐본다.
  ```
  // state가 없는 상태에서 1초씩 움직이는 시계
  function Clock(props) {
    return (
      <div>
        <h1>Hello, world!</h1>
        <h2>It is {props.date.toLocaleTimeString()}.</h2>
      </div>
    );
  }

  function tick() {
    ReactDOM.render(
      <Clock date={new Date()} />,
      document.getElementById('root')
    );
  }

  setInterval(tick, 1000);
  ```

### Converting a Function to a Class
1. `React.Component`를 상속받는 ES6 클래스를 만든다.
2. `render()` 메서드를 호출한다.
3. 함수 컴포넌트의 `render()` 메서드 안으로 옮긴다.
4. `props`를 `render()` 안에서 `this.props`로 변경한다.

- 결과: `Clock` 컴포넌트는 클래스로 정의됐다. `render` 메서드는 변화가 있을 때마다 호출된다.
  ```
  class Clock extends React.Component {
    render() {
      return (
        <div>
          <h1>Hello, world!</h1>
          <h2>It is {this.props.date.toLocaleTimeString()}.</h2>
        </div>
      );
    }
  }
  ```

### 클래스에 State 추가하기
1. 클래스 생성자(constructor)를 추가한다.
2. state를 정의하고, props를 받아온다.
  ```
  class Clock extends React.Component {
    constructor(props) {
      super(props);
      this.state = {date: new Date()};
    }

    render() {
      return (
        <div>
          <h1>Hello, world!</h1>
          <h2>It is {this.state.date.toLocaleTimeString()}.</h2>
        </div>
      );
    }
  }

  ReactDOM.render(
    <Clock />,
    document.getElementById('root')
  );
  ```

### 클래스에 Lifecycle 메서드 추가
- `componentDidMount()`는 컴포넌트가 DOM으로 렌더된 후에 실행된다.
- `componentWillUnmount()`는 컴포넌트가 DOM에서 제거될때 실행된다.
- 위의 두 메서드를 이용해서 시계를 작동시킨다. 
  ```
  class Clock extends React.Component {
    constructor(props) {
      super(props);
      this.state = {date: new Date()};
    }

    componentDidMount() {
      this.timerID = setInterval(
        () => this.tick(),
        1000
      );
    }

    componentWillUnmount() {
      clearInterval(this.timerID);
    }

    tick() {
      this.setState({
        date: new Date()
      });
    }

    render() {
      return (
        <div>
          <h1>Hello, world!</h1>
          <h2>It is {this.state.date.toLocaleTimeString()}.</h2>
        </div>
      );
    }
  }

  ReactDOM.render(
    <Clock />,
    document.getElementById('root')
  );
  ```
- 작동 단계
  1. `<Clock />`이 `ReactDOM.render()`로 전달됐을 때, 리액트는 `Clock` 컴포넌트의 constructor를 호출. -> this.state를 초기화
  2. 리액트는 `Clock` 컴포넌트의 `render()`메서드를 호출. -> 리액트는 화면에 표시돼야 할 내용을 앎. -> 이에 맞게 DOM을 업데이트
  3. `Clock`의 출력 값이 DOM에 반영되면 `componentDidMount()` 호출 -> 시계 시작(`tick()`메서드)
  4. 브라우저는 매초 `tick()`을 호출하고, `setState()`를 통해 state가 변경. -> 리액트는 이에 맞게 DOM을 변경
  5. `Clock` 컴포넌트가 DOM에서 삭제된다면 `componentWillUnmount()` 호출 -> 시계 멈춤

### State 올바르게 사용하기
1. state를 직접적으로 수정하지 말아라
  ```
  // Wrong
  this.state.comment = 'Hello';

  // Correct
  this.setState({comment: 'Hello'});
  ```
2. State는 비동기적으로Asynchronous 업데이트 될 수 있다.
  - `setState`안에 객체 대신 함수를 넣어서 비동기 문제를 해결할 수 있다.
  - 함수의 첫번째 인자는 이전의 state가, 두번째 인자에는 업데이트된 props가 들어간다.
    ```
    // 현재의 state값에서 props를 받아서 더하고 새로운 state를 만드는 예제
    // Wrong
    this.setState({
      counter: this.state.counter + this.props.increment,
    });

    // Correct
    this.setState((state, props) => ({
      counter: state.counter + props.increment
    }));
    ```

  3. State Updates are Merged
    - state의 일부만 변경하면 변경된 사항이 기존 state에 병합된다.
    - 단, 병합은 얕게shallow 이뤄진다.
      ```
      constructor(props) {
          super(props);
          this.state = {
            posts: [],
            comments: []
          };
        }
      componentDidMount() {
        fetchPosts().then(response => {
          this.setState({
            posts: response.posts
          });
        });

        fetchComments().then(response => {
          this.setState({
            comments: response.comments
          });
        });
      }
      ```

### 데이터는 아래로 흐른다.
- 부모 컴포넌트는 state를 자식컴포넌트의 props로 넘겨주는 경우도 있는데, 받는 입장에서는 손으로 직접 타이핑한 것과 state를 넘겨준 것 사이에 전혀 차이가 없다.
- 하향식top-down, 혹은 단방향식unidirectional 
  - state는 오직 하위 컴포넌트에만 영향을 줄 수 있다.


## [Handling Events](https://ko.reactjs.org/docs/handling-events.html)
- 리액트에서 이벤트를 구현하는 것은 DOM 엘리먼트에서와 유사하지만, 몇가지 차이점이 있다.
- 리액트 이벤트 이름은 camelCase를 쓴다.
- event handler는 string보다 함수로 넘겨준다.
  ```
  // DOM
  <button onclick="activateLasers()">
    Activate Lasers
  </button>

  // React
  <button onClick={activateLasers}>
    Activate Lasers
  </button>
  ```
- 기본동작을 방지하기 위해 `false`를 반환하는 대신 `preventDefault`를 사용한다.
  ```
  // DOM
  <a href="#" onclick="console.log('The link was clicked.'); return false">
    Click me
  </a>

  // React
  function ActionLink() {
    function handleClick(e) {
      e.preventDefault();
      console.log('The link was clicked.');
    }

    return (
      <a href="#" onClick={handleClick}>
        Click me
      </a>
    );
  }
  ```
- 리스너 추가: 리액트에서는 DOM 생성 후 `addEventListener`를 호출하지 않고, 엘리먼트가 처음 렌더링될 때 리스너를 제공한다.
  ```
  class Toggle extends React.Component {
    constructor(props) {
      super(props);
      this.state = {isToggleOn: true};

      // 콜백에서 `this`가 작동하려면 아래와 같이 바인딩 해주어야 합니다.
      this.handleClick = this.handleClick.bind(this);
    }

    handleClick() {
      this.setState(state => ({
        isToggleOn: !state.isToggleOn
      }));
    }

    render() {
      return (
        <button onClick={this.handleClick}>
          {this.state.isToggleOn ? 'ON' : 'OFF'}
        </button>
      );
    }
  }

  ReactDOM.render(
    <Toggle />,
    document.getElementById('root')
  );
  ```
  - `this` 바인딩: 메서드는 기본적으로 바인드 되어있지 않다. 바인딩하지 않으면 `this`는 `undefined`상태다.
    - constructor 내에서 바인딩(정석적인 방법)
      - `this.handleClick = this.handleClick.bind(this);`
    - public class fields syntax 사용 (실험적인 방법)
      - Babel을 통해 사용가능한 문법으로 바뀌는듯?
      ```
      handleClick = () => {
        console.log('this is:', this);
      }
      ```
    - 화살표 함수 사용 (ES6 문법 참고)
      - 문제점!: 렌더링될 때마다 다른 콜백이 생성된다. 콜백이 하위 컴포넌트에 props로 전달되면 그 컴포넌트는 다시 렌더링을 수행할 수 있다. -> 이 문제를 피하려면 위의 방법을 사용하는 것이 좋다.
      ```
      class LoggingButton extends React.Component {
        handleClick() {
          console.log('this is:', this);
        }

        render() {
          // 이 문법은 `this`가 handleClick 내에서 바인딩되도록 합니다.
          return (
            <button onClick={() => this.handleClick()}>
              Click me
            </button>
          );
        }
      }
      ```
### 이벤트 핸들러에 인자 전달
- `id`를 전달하고 싶을 때, 아래 두 줄 모두 정상적으로 작동한다.
  ```
  <button onClick={(e) => this.deleteRow(id, e)}>Delete Row</button>
  <button onClick={this.deleteRow.bind(this, id)}>Delete Row</button>
  ```