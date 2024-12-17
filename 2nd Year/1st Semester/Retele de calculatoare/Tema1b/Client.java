import java.net.*;
import java.io.*;
import java.util.*;


public class Client {
    public static void main(String[] args) {
        try {

            String ip=args[0];
            int port=Integer.parseInt(args[1]);

            Socket c = new Socket(ip,port);
            System.out.println("Connected to the server.");


            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));


            DataInputStream socketIn = new DataInputStream(c.getInputStream());
            DataOutputStream socketOut = new DataOutputStream(c.getOutputStream());


            System.out.print("Numar = ");
            int a = Integer.parseInt(reader.readLine());


            socketOut.writeShort(a);
            socketOut.flush();


            System.out.print("Sirul divizorilor este: ");
            while (true) {
                try {

                    int divisor = socketIn.readUnsignedShort();
                    System.out.print(divisor + " ");
                } catch (EOFException e) {

                    break;
                }
            }

            System.out.println();

            reader.close();
            socketIn.close();
            socketOut.close();
            c.close();
        } catch (IOException e) {
            System.out.println("Eroare la conectarea la server: " + e.getMessage());
        }
    }
}
