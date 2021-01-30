import 'package:flutter/material.dart';
import 'package:webview_flutter/webview_flutter.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        primarySwatch: Colors.pink,
        visualDensity: VisualDensity.adaptivePlatformDensity,
      ),
      home: MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  int _counter = 0;

  void _incrementCounter() {
    setState(() {
      _counter++;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
          child: Column(children: [
          Expanded(
            child: WebView(
                initialUrl: Uri.dataFromString(
                        '<iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1293073/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15"></iframe>',
                        mimeType: 'text/html')
                    .toString(),
                javascriptMode: JavascriptMode.unrestricted)),
            Expanded(
                child: WebView(
                    initialUrl: Uri.dataFromString(
                        '<iframe width="450" height="260" style="border: 1px solid #cccccc;" src="https://thingspeak.com/channels/1293073/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=60&type=line&update=15"></iframe>',
                        mimeType: 'text/html')
                        .toString(),
                    javascriptMode: JavascriptMode.unrestricted)),

      ]),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: _incrementCounter,
        tooltip: 'Increment',
        child: Icon(Icons.add),
      ),
    );
  }
}
