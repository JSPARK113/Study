import React from 'react';
import PropTypes from 'prop-types';
import './Counter.css';

// presentational 컴포넌트

class Counter extends React.Component {
    render() {
        const {number, color, onIncrement, onDecrement, onSetColor} = this.props;
        return (
            <div
                className="Counter"
                // 왼쪽 버튼 클릭하면 1 더하기
                onClick={onIncrement}
                // 오른쪽 버튼 클릭하면 1 빼기
                onContextMenu={
                    (e) => {
                        e.preventDefault();
                        onDecrement();
                    }
                }
                // 더블 클릭하면 색 변경
                onDoubleClick={onSetColor}
                style={{backgroundColor: color}}>
                {number}
            </div>
        );
    }
}

// 함수형 컴포넌트로 작성할 경우

// const Counter = ({number, color, onIncrement, onDecrement, onSetColor}) => {
//     return (
//         <div
//             className="Counter"
//             // 왼쪽 버튼 클릭하면 1 더하기
//             onClick={onIncrement}
//             // 오른쪽 버튼 클릭하면 1 빼기
//             onContextMenu={
//                 (e) => {
//                     e.preventDefault();
//                     onDecrement();
//                 }
//             }
//             // 더블 클릭하면 색 변경
//             onDoubleClick={onSetColor}
//             style={{backgroundColor: color}}>
//             {number}
//         </div>
//     );
// };

Counter.propTypes = {
    number: PropTypes.number,
    color: PropTypes.string,
    onIncrement: PropTypes.func,
    onDecrement: PropTypes.func,
    onSetColor: PropTypes.func
};

Counter.defaultProps = {
    number: 0,
    color: 'black',
    onIncrement: () => console.warn('onIncrement not defined'),
    onDecrement: () => console.warn('onDecrement not defined'),
    onSetColor: () => console.warn('onSetColor not defined'),
};

export default Counter;