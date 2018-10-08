package cn;

import java.io.*;
import java.net.*;

public class tcpGroupServ {


  static ServerSocket servSock = null;

  static Socket cliSock = null;

  static final int maxCli = 20;
  static final clients[] threads = new clients[maxCli];

  public static void main(String args[]) {
    int port = 9999;
    try {
      servSock = new ServerSocket(port);
    while (true) {
        System.out.print("\nWaiting For clients\n");
        cliSock = servSock.accept();
        int i = 0;
        for (i = 0; i < maxCli; i++) {
          if (threads[i] == null) {
            (threads[i] = new clients(cliSock, threads)).start();
            break;
          }
        }
        if (i == maxCli) {
          PrintStream os = new PrintStream(cliSock.getOutputStream());
          os.println("Server Full");
          os.close();
          cliSock.close();
        }
    }
    }
    catch(Exception e)
    {
        System.out.println(e.getMessage());
    }
  }
}


class clients extends Thread {

  private DataInputStream is = null;
  private PrintStream os = null;
  private Socket cliSock = null;
  private final clients[] threads;
  private int maxCli;

  public clients(Socket cliSock, clients[] threads) {
    this.cliSock = cliSock;
    this.threads = threads;
    maxCli = threads.length;
  }

  public void run() {
    int maxCli = this.maxCli;
    clients[] threads = this.threads;

    try {

      is = new DataInputStream(cliSock.getInputStream());
      os = new PrintStream(cliSock.getOutputStream());
      os.println("Enter usrid ");
      String id = is.readLine().trim();
      System.out.println("client "+id+" connected");
      os.println("Hello " + id
          + " Welcome To Chat Room To exit type $$");
      for (int i = 0; i < maxCli; i++) {
        if (threads[i] != null && threads[i] != this) {
          threads[i].os.println("User" + id
              + " Has Entered The Room");
        }
      }
      while (true) {
        String line = is.readLine();
        if (line.startsWith("$$")) {
          break;
        }
        for (int i = 0; i < maxCli; i++) {
          if (threads[i] != null) {
            threads[i].os.println( id + ">> " + line);
          }
        }
      }
      for (int i = 0; i < maxCli; i++) {
        if (threads[i] != null && threads[i] != this) {
          threads[i].os.println( id
              + " Left The Room");
        }
      }
      os.println("Byee");

      for (int i = 0; i < maxCli; i++) {
        if (threads[i] == this) {
          threads[i] = null;
        }
      }

      is.close();
      os.close();
      cliSock.close();
    } catch (IOException e) {
    }
  }
}

