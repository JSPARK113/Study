import React, { Component } from 'react';
import queryString from 'query-string';

class ParamsQuery extends Component {
    render() {
        // 컴포넌트가 받는 props 중 location을 통해 경로 파라미터를 가져온다.
        // location의 search 값을 파싱해서 쿼리 값에 대한 object를 얻는다.
        const query = queryString.parse(this.props.location.search);
        return (
            <div>
                <h2>Params 화면</h2>
                <div>입력한 query 파라미터의 content 값은</div>
                {/*query로 content의 값을 보내는 경우*/}
                <div><b>{query.content}</b> 입니다.</div>
            </div>
        );
    }
}

export default ParamsQuery;
