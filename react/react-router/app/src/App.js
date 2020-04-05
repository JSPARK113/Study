import React, { Component } from 'react';
import {BrowserRouter, Route} from "react-router-dom";
import Home from './pages/Home';
import About from './pages/About';
import ParamsPath from './pages/ParamsPath';
import ParamsQuery from './pages/ParamsQuery';
import Topics from './pages/Topics';
import Menu from "./components/Menu";
import NavMenu from "./components/NavMenu";

class App extends Component {
  render() {
    return (
        <div>
            {/*react-router 기능을 사용하는 컴포넌트는 BrowserRouter 태그 안에 넣어준다.*/}
            <BrowserRouter>
                <Menu/>
                <NavMenu/>
                <h3>
                    ===== Route를 적용한 페이지 =====
                </h3>
                {/*exact를 붙이면 정확히 일치하는 path에 대해서 작동*/}
                <Route exact path="/" component={Home}/>
                <Route exact path="/about" component={About}/>
                {/*파라미터가 포함된 주소*/}
                {/*path 파라미터*/}
                <Route path="/params_path/:content" component={ParamsPath}/>
                <Route path="/params_query" component={ParamsQuery}/>
                <Route path="/topics" component={Topics}/>
            </BrowserRouter>
        </div>
    );
  }
}

export default App;
