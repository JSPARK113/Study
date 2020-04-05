import React, { Component } from 'react';
import {Link, Route} from 'react-router-dom';
import Topic from './Topic';

class Topics extends Component {
    render() {
        const {match}= this.props;
        return (
            <div>
                <h2>Topics 화면</h2>
                {/* 각 Topic에 대한 링크 */}
                <ul>
                    <li><Link to={`${match.url}/1`}>Topic 1</Link></li>
                    <li><Link to={`${match.url}/2`}>Topic 2</Link></li>
                    <li><Link to={`${match.url}/3`}>Topic 3</Link></li>
                </ul>
                <h3>Topic 컴포넌트 페이지</h3>
                {/*topic이 선택되지 않았을 때 문구 표시*/}
                <Route exact path={`${match.path}`}
                       render={() => <div>topic을 선택해주세요.</div>}/>
                 {/*topic이 선택됐을 때 Topic 컴포넌트 렌더링*/}
                <Route path={`${match.path}/:id`} component={Topic}/>
            </div>
        );
    }
}

export default Topics;
