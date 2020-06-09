# Main Concepts

## 목차
1. [JSX](#JSX)
2. [엘리먼트 렌더링](#엘리먼트-렌더링)
3. [Components와 Props](#Components와-Props)

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

### 변경된 부분만 업데이트
- React DOM은 해당 엘리먼트(+자식 엘리먼트)를 이전 엘리먼트와 비교하고, 필요한 경우에만 DOM을 업데이트한다.

## [Components와 Props](https://ko.reactjs.org/docs/components-and-props.html)
- 