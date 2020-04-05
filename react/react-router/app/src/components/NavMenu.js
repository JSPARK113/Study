import React, { Component } from 'react';
import { NavLink } from 'react-router-dom';

class Menu extends Component {
    render() {
        const activeStyle = {
            color: '#2b61d2',
            fontWeight: 'bold'
        };
        return (
            <div>
                <h3>NavLink 컴포넌트를 사용한 Menu</h3>
                <li><NavLink exact to="/" activeStyle={activeStyle}> Home </NavLink></li>
                <li><NavLink exact to="/about" activeStyle={activeStyle}> About </NavLink></li>
                <li>
                    <NavLink to="/params_path/path_params_example" activeStyle={activeStyle}>
                        경로 파라미터 예제
                    </NavLink>
                    : /params_path/path_params_example
                </li>
                <li>
                    <NavLink to="/params_query?content=query_params_example" activeStyle={activeStyle}>
                        쿼리 파라미터 예제
                    </NavLink>
                    : 경로가 아닌 쿼리파라미터에서는 NavLink의 activeStyle이 제대로 작동하지 않음
                </li>
                <hr/>
            </div>
        );
    }
}

export default Menu;