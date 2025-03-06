import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
public class GenerateTestData {
    public static void main(String[] args) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(args[0]))) {
            Random random = new Random();
            int n = random.nextInt(1000)+1;
            // int s = random.nextInt(10)+1;
            writer.write(n + "\n");
            char[] a=new char[100];
            String[] n1=new String[1001];
            String[] n2=new String[1001];
            int stat=65;
            for(int i=0;i<26*2;i++)
            {
                a[i]=(char) stat;
                stat++;
            }
            int save;
            List<Integer> numbers = new ArrayList<>();

            for (int i = 0; i < n; i++){
                save=i;
                n1[i]=Character.toString(a[save%52]);
                save/=52;
                while(save>0)
                {
                    n1[i]=n1[i]+a[save%52];
                    save/=52;
                }
                writer.write(n1[i] + " ");
                numbers.add(i);
            }
            writer.write("\n");
            for (int i = 0; i < n; i++){
                save=i;
                n2[i]=Character.toString(a[save%52]);
                save/=52;
                while(save>0)
                {
                    n2[i]=n2[i]+a[save%52];
                    save/=52;
                }
                writer.write(n2[i] + " ");
            }
            for (int i = 0; i < n; i++){
                Collections.shuffle(numbers);
                writer.write("\n");
                for(int j=0;j<n;j++) {
                    writer.write(n1[numbers.get(j)] + " ");
                }
            }
            for (int i = 0; i < n; i++){
                Collections.shuffle(numbers);
                writer.write("\n");
                for(int j=0;j<n;j++) {
                    writer.write(n2[numbers.get(j)] + " ");
                }
            }
            writer.write("\n");
        } catch (IOException e)
        {

        }
    }
}
