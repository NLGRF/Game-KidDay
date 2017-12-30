import React, { Component } from 'react';
import './App.css';
import 'bulma/css/bulma.css'
class App extends Component {
    constructor(){
      super();
      this.state={
          value:101
      }

    }
    oNClick(){
          let  ran =0;
          ran = Math.floor((Math.random() * 10000));
          this.setState({value:ran})
    }
    render() {
        return ( <div className = "App" >
            <div className = "layOut" >
                 <div className = "Title" > Game 24 </div>
                 <div className="por">{this.state.value}</div>
                 <div onClick={this.oNClick.bind(this)} className="button is-danger"><h1><a>Ran</a></h1></div>
            </div> 
            </div>
        );
    }
}

export default App;