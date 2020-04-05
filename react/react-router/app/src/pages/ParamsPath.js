import React, { Component } from 'react';

class ParamsPath extends Component {
    render() {
        // 컴포넌트가 받는 props 중 match 통해 경로 파라미터를 가져온다.
        // match.params.<파라미터이름>에 값이 있다.
        const {match} = this.props;
        return (
            <div>
                <h2>Params 화면</h2>
                <div>입력한 path 파라미터는</div>
                <div><b>{match.params.content}</b> 입니다.</div>
            </div>
        );
    }
}

export default ParamsPath;
