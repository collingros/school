import 'package:flutter/material.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      home: new FirstScreen(),
    );
  }
}

class FirstScreen extends StatelessWidget {
  @override
  Widget build (BuildContext context) {
    return new Scaffold(
        appBar: new AppBar(
          title: new Text("You have entered the danger zone"),
        ),
        body: new Checkbox(
            value: false,
            onChanged: (bool newValue){
              Navigator.push(context,
                  new MaterialPageRoute(builder: (context) => new SecondScreen()));
            }
        )
    );
  }
}

class SecondScreen extends StatelessWidget {
  @override
  Widget build (BuildContext context) {
    return new Scaffold(
        appBar: new AppBar(
          title: new Text("I see you, cheeky bugger"),
        ),
        body: new Checkbox(
            value: false,
            onChanged: (bool newValue) {
              Navigator.push(context, // Pop from stack
              new MaterialPageRoute(builder: (context) => new FirstScreen()));
            }
        )
    );
  }
}


