import React, { Component } from 'react';

class Topic extends Component {
    render() {
        const {match}= this.props;
        return (
            <div>
                topic id : {match.params.id}
            </div>
        );
    }
}

export default Topic;
