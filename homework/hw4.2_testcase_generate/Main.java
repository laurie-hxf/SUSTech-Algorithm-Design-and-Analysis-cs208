import java.util.Arrays;
import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        QReader in = new QReader();
        QWriter out = new QWriter();
        int n = in.nextInt();
        int m = in.nextInt();
        node[] t = new node[n + 1];
        for (int i = 0; i <= n; i++) {
            t[i] = new node();
            t[i].sign = i;
        }
        for (int i = 1; i <= m; i++) { 
            int u = in.nextInt();
            int v = in.nextInt();
            int w = in.nextInt();
            t[u].way.add(new edge(u, v, w));
            t[v].way1.add(new edge(v, u, w));
        }
        PriorityQueue<node> numbers = new PriorityQueue<>(100001, new CustomComparator());
        t[1].value = 0;
        numbers.offer(t[1]);
        node now;
        while (!numbers.isEmpty()) {
            now = numbers.poll();
            now.vis = true;
            for (int i = 0; i < now.way.size(); i++) {
                if (!t[now.way.get(i).v].vis) {
                    if (!t[now.way.get(i).v].en) {
                        t[now.way.get(i).v].value = now.value + now.way.get(i).num;
                        numbers.offer(t[now.way.get(i).v]);
                        t[now.way.get(i).v].en=true;
                    } else if (now.value + now.way.get(i).num < t[now.way.get(i).v].value) {
                        numbers.remove(t[now.way.get(i).v]);
                        t[now.way.get(i).v].value = now.value + now.way.get(i).num;
                        numbers.offer(t[now.way.get(i).v]);
                    }
                }
            }
        }
        long sum=0;
        long small;
        for (int i = 2; i <= n; i++) {
            small=Integer.MAX_VALUE;
            for(int j=0;j<t[i].way1.size();j++)
            {
                if(t[i].value==t[t[i].way1.get(j).v].value+t[i].way1.get(j).num) {
                    small=Math.min(small,t[i].way1.get(j).num);
                }
            }
            sum+=small!=Integer.MAX_VALUE?small:0;
        }
        out.println(sum);
        out.close();
    }

}

class CustomComparator implements Comparator<node> {
    @Override
    public int compare(node number1, node number2) {
        return number1.value - number2.value;
    }
}


class node {
    boolean vis = false;
    boolean en = false;
    int value = Integer.MAX_VALUE;
    int sign;
    List<edge> way = new ArrayList<>();
    List<edge> way1 = new ArrayList<>();
}

class edge {
    int u;
    int v;
    int num;

    public edge(int u, int v, int num) {
        this.u = u;
        this.v = v;
        this.num = num;
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