import React from 'react';
import ReactDOM from 'react-dom';
import App from './containers/App';
import './index.css';

// Redux 관련 컴포넌트 임포트
import {createStore} from 'redux'
import reducers from './reducers'
import {Provider} from "react-redux";

// store 생성
const store = createStore(reducers);

ReactDOM.render(
    // 스토어와 리액트 앱을 연결하기 위해 Provider로 App을 감싸준다.
    <Provider store={store}>
        <App />
    </Provider>,
    document.getElementById('root')
);