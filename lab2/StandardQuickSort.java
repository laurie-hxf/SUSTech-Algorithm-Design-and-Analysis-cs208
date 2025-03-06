import java.io.*;
import java.util.*;
import java.util.Scanner;

public class StandardQuickSort {
    public static void main(String[] args) {
        QReader in = new QReader();
        QWriter out = new QWriter();
        int n = in.nextInt();
        String[] a = new String[n+1];
        String[] b = new String[n+1];
        int[][] ranka=new int[n+1][n+1];
        int[][] rankb=new int[n+1][n+1];
        int[] matcha=new int[n+1];
        int[] matchb=new int[n+1];
        String t;
        Map<String, Integer> hasha = new HashMap<>();
        for (int i = 1; i <= n; i++) {
            a[i] = in.next();
            hasha.put(a[i], i);
        }
        Map<String, Integer> hashb = new HashMap<>();
        for (int i = 1; i <= n; i++) {
            b[i] = in.next();
            hashb.put(b[i], i);
        }
        int value=0;
        String st;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                st=in.next();
                value=hashb.get(st);
                ranka[i][j]=value;
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                st=in.next();
                value=hasha.get(st);
                rankb[i][value]=j;
            }
        }
        int count=1;
        int now=1,tran;
        int i;
        while (count<=n)
        {
            if(matcha[now]==0)
            {
                i=1;
                while(i<=n) {
                    if (matchb[ranka[now][i]] == 0) {
                        matcha[now] = ranka[now][i];
                        matchb[ranka[now][i]] = now;
                        count++;
                        now=count;
                        break;
                    } else {
                        if (rankb[ranka[now][i]][now] < rankb[ranka[now][i]][matchb[ranka[now][i]]])
                        {
                            matcha[now] = ranka[now][i];
                            matcha[matchb[ranka[now][i]]] = 0;//todo将matchb[ranka[now][i]]对应的旧man设回无匹配
                            tran=matchb[ranka[now][i]];
                            matchb[ranka[now][i]] = now;
                            now=tran;
                            break;
                        }else
                        {
                            i++;
                        }
                    }
                }
                if(i>n) break;
            }
        }
        for(int j=1;j<=n;j++)
        {
            out.print(a[j]);
            out.print(" ");
            out.println(b[matcha[j]]);
        }
        out.close();
    }
}


class QReader {
    private BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    private StringTokenizer tokenizer = new StringTokenizer("");

    private String innerNextLine() {
        try {
            return reader.readLine();
        } catch (IOException e) {
            return null;
        }
    }

    public boolean hasNext() {
        while (!tokenizer.hasMoreTokens()) {
            String nextLine = innerNextLine();
            if (nextLine == null) {
                return false;
            }
            tokenizer = new StringTokenizer(nextLine);
        }
        return true;
    }

    public String nextLine() {
        tokenizer = new StringTokenizer("");
        return innerNextLine();
    }

    public String next() {
        hasNext();
        return tokenizer.nextToken();
    }

    public int nextInt() {
        return Integer.parseInt(next());
    }

    public long nextLong() {
        return Long.parseLong(next());
    }
}

class QWriter implements Closeable {
    private BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));

    public void print(Object object) {
        try {
            writer.write(object.toString());
        } catch (IOException e) {
            return;
        }
    }

    public void println(Object object) {
        try {
            writer.write(object.toString());
            writer.write("\n");
        } catch (IOException e) {
            return;
        }
    }

    @Override
    public void close() {
        try {
            writer.close();
        } catch (IOException e) {
            return;
        }
    }
}