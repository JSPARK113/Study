// ActionTypes의 모든 상수 가져오기
import * as types from './ActionTypes';

// 액션 생성자

export const increment = () => ({
    type: types.INCREMENT
});

export const decrement = () => ({
    type: types.DECREMENT
});

// 파라미터로 color 값을 받아야 함.
export const setColor = (color) => ({
    type: types.SET_COLOR,
    color
});