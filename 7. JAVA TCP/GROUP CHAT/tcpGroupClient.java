package cn;

import java.io.*;
import java.net.*;

public class tcpGroupClient implements Runnable {

  static Socket cliSock = null;
  static PrintStream os = null;
  static DataInputStream is = null;

  static BufferedReader inputLine = null;
  static boolean closed = false;
  
  public static void main(String[] args) {

    int portNumber = 9999;
    String host = "localhost";


    try {
      cliSock = new Socket(host, portNumber);
      inputLine = new BufferedReader(new InputStreamReader(System.in));
      os = new PrintStream(cliSock.getOutputStream());
      is = new DataInputStream(cliSock.getInputStream());
    } catch (Exception e) {
        System.out.println(e.getMessage());
    }

    if (cliSock != null && os != null && is != null) {
      try {

        new Thread(new tcpGroupClient()).start();
        while (!closed) {
          os.println(inputLine.readLine().trim());
        }
        os.close();
        is.close();
        cliSock.close();
      } catch (IOException e) {
        System.err.println("IOException:  " + e);
      }
    }
  }

  public void run() {
    
    String responseLine;
    try {
      while ((responseLine = is.readLine()) != null) {
        System.out.println(responseLine);
        if (responseLine.indexOf("*** Bye") != -1)
          break;
      }
      closed = true;
    } catch (IOException e) {
      System.err.println("IOException:  " + e);
    }
  }
}
