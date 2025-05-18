//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by FernFlower decompiler)
//

import java.util.PriorityQueue;

public class Main {

    public static void main(String[] args) {
        QReader in = new QReader();
        QWriter out = new QWriter();
        int n = in.nextInt();
        int m = in.nextInt();
        node[] t = new node[n + 1];

        int i;
        for(i = 0; i <= n; t[i].sign = i++) {
            t[i] = new node();
        }

        int i;
        for(i = 1; i <= m; ++i) {
            int u = in.nextInt();
            i = in.nextInt();
            int w = in.nextInt();
            t[u].way.add(new edge(u, i, w));
            t[i].way1.add(new edge(i, u, w));
        }

        PriorityQueue<node> numbers = new PriorityQueue(100001, new CustomComparator());
        t[1].value = 0;
        numbers.offer(t[1]);

        while(!numbers.isEmpty()) {
            node now = (node)numbers.poll();
            now.vis = true;

            for(i = 0; i < now.way.size(); ++i) {
                if (!t[((edge)now.way.get(i)).v].vis) {
                    if (!t[((edge)now.way.get(i)).v].en) {
                        t[((edge)now.way.get(i)).v].value = now.value + ((edge)now.way.get(i)).num;
                        numbers.offer(t[((edge)now.way.get(i)).v]);
                        t[((edge)now.way.get(i)).v].en = true;
                    } else if (now.value + ((edge)now.way.get(i)).num < t[((edge)now.way.get(i)).v].value) {
                        numbers.remove(t[((edge)now.way.get(i)).v]);
                        t[((edge)now.way.get(i)).v].value = now.value + ((edge)now.way.get(i)).num;
                        numbers.offer(t[((edge)now.way.get(i)).v]);
                    }
                }
            }
        }

        long sum = 0L;

        for(int i = 2; i <= n; ++i) {
            long small = 2147483647L;

            for(int j = 0; j < t[i].way1.size(); ++j) {
                if (t[i].value == t[((edge)t[i].way1.get(j)).v].value + ((edge)t[i].way1.get(j)).num) {
                    small = Math.min(small, (long)((edge)t[i].way1.get(j)).num);
                }
            }

            sum += small;
        }

        out.println(sum);
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