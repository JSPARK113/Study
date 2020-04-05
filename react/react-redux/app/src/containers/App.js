import React, { Component } from 'react';
import CounterContainer from './CounterContainer'

class App extends Component {
    render() {
        return (
            <div>
                <div>
                    <li>한번 클릭 - 1 증가</li>
                    <li>더블 클릭 - 2 증가 & 색변경</li>
                    <li>마우스 오른쪽버튼 클릭 - 1 감소</li>
                </div>
                {/*App에서 Container 컴포넌트를 불러온다.*/}
                <CounterContainer/>
            </div>
        );
    }
}

export default App;
