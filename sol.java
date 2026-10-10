import java.io.*;
import java.util.*;

public class Main {

    static class FastScanner {
        private final InputStream in = System.in;
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;

        private int read() throws IOException {
            if(ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if(len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        int nextInt() throws IOException {
            int c;
            do {
                c = read();
            } while(c <= ' ');

            int sign = 1;

            if(c == '-') {
                sign = -1;
                c = read();
            }

            int val = 0;

            while(c > ' ') {
                val = val * 10 + c - '0';
                c = read();
            }

            return val * sign;
        }
    }


    static final long MOD = 1_000_000_007L;


    static void solve(FastScanner fs, StringBuilder out) throws Exception {

    }


    public static void main(String[] args) throws Exception {

        FastScanner fs = new FastScanner();
        StringBuilder out = new StringBuilder();

        int t = fs.nextInt();

        while(t-- > 0) {
            solve(fs,out);
        }

        System.out.print(out);
    }
}