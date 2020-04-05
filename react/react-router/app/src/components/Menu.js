import React, { Component } from 'react';
import { Link } from 'react-router-dom';

class Menu extends Component {
    render() {
        return (
            <div>
                <h3>Link 컴포넌트를 사용한 Menu</h3>
                <li><Link to="/"> Home </Link></li>
                <li><Link to="/about"> About </Link></li>
                <li>
                    <Link to="/params_path/path_params_example">
                        경로 파라미터 예제
                    </Link>
                    : /params_path/path_params_example
                </li>
                <li>
                    <Link to="/params_query?content=query_params_example">
                        쿼리 파라미터 예제
                    </Link>
                    : /params_query?content=query_params_example
                </li>
                <li>
                    <Link to="/topics">
                        Topics
                    </Link>
                </li>
                <hr/>
            </div>
        );
    }
}

export default Menu;