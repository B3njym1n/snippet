package org.example;

import io.vavr.collection.Array;
import org.apache.commons.logging.Log;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.*;
import java.util.stream.Collectors;


public class SortTest {

    private static Logger logger = LoggerFactory.getLogger(SortTest.class);
    public static void main(String[] args) {
        Random rand = new Random();
        Array<Integer> a = Array.range(1, 17).shuffle(rand);
//        a.forEach(System.out::println);
//        Comparator<Integer> cc = (m, n) -> n - m;

//        a.sortBy(l -> l.byteValue()).forEach(System.out::println);
//        a.sortBy((m, n) -> n - m, e -> e.intValue()).forEach(System.out::println);
        List<String> b = Array.rangeClosed('A', 'Z').crossProduct(Array.rangeClosed('A', 'Z')).toJavaStream().map(t -> new StringBuilder().append(t._1).append(t._2).toString()).collect(Collectors.toList());
        Array<String> cs = Array.ofAll(b);
        Array<String> ds = Array.range(0, 1000).map(i -> String.format("%04d", i));
        Array<String> es = Array.range(0,10).map(i -> String.format("%02d", i));
//        Array<String> before = cs.zipWith(ds, (m, n) -> m + n).shuffle(rand);
        Array<String> before = cs.crossProduct(es).map(t -> t._1 + t._2).toArray().shuffle(rand);
        /*Array<Character> numchars = Array.rangeClosed('0', '9').appendAll(Array.rangeClosed('a', 'z')).appendAll(Array.rangeClosed('A', 'Z')).shuffle();
        System.out.println(numchars.size());
        numchars.sorted().forEach(System.out::println);*/

//        before.forEach(System.out::println);
        Comparator<String> cc = (s1, s2) -> {
            int pos = 4;
            int diff;
            do {
               diff = s1.charAt(pos - 1) - s2.charAt(pos - 1);
               pos--;
            } while (diff == 0 && pos > 0);
//            logger.info("{} {} {}", s1, s2, diff);
            return diff;
        };
        before.sorted(cc).forEach(System.out::println);
    }

    public void test1() {
        List<Item> list = new ArrayList<>();
        Item i1 = new Item("100-A01A", "item1");
        Item i2 = new Item("100-A02A", "item2");
        Item i3 = new Item("100-A03A", "item3");
        Item i4 = new Item("101-A01A", "item4");
        Item i5 = new Item("101-A01B", "item5");
        Item i6 = new Item("101-A02A", "item6");
        Item i7 = new Item("102-A01A", "item7");
        list.add(i1);
        list.add(i2);
        list.add(i3);
        list.add(i4);
        list.add(i5);
        list.add(i6);
        list.add(i7);
        Collections.shuffle(list);
        list.forEach(e -> System.out.println("code: " + e.code + " name: " + e.name));

        /*Comparator<Item> sss = (p, n) -> {
            String c1 = p.code;
            String c2 = n.code;
        }*/
        /*List<Item> list2 = list.stream().sorted((a, b) -> {
            String c1 = a.code;
            String c2 = b.code;
            String[] parts1 = c1.split("-");
            String[] parts2 = c2.split("-");
            if (Integer.parseInt(parts1[0]) < Integer.parseInt(parts2[0])) {
                return -1;
            } else if (Integer.parseInt(parts1[0]) > Integer.parseInt(parts2[0])) {
                return 1;
            } else {
                if (parts1[1].charAt(0) < parts2[1].charAt(0)) {
                    return -1;
                } else if (parts1[1].charAt(0) > parts2[1].charAt(0)) {
                    return 1;
                } else {
                    if (Integer.parseInt(parts1[1].substring(1,3)) < Integer.parseInt(parts2[1].substring(1,3))) {
                        return -1;
                    } else if (Integer.parseInt(parts1[1].substring(1,3)) > Integer.parseInt(parts2[1].substring(1,3))) {
                        return 1;
                    } else {
                        if (parts1[1].charAt(3) < parts2[1].charAt(3)) {
                            return -1;
                        } else if (parts1[1].charAt(3) > parts2[1].charAt(3)) {
                            return 1;
                        } else {
                            return 0;
                        }
                    }
                }
            }
        }).collect(Collectors.toList());
        list2.forEach(e -> System.out.println("code: " + e.code + " name: " + e.name));*/
    }
}

class Item {
    String code;
    String name;

    public Item(String code, String name) {
        this.code = code;
        this.name = name;
    }
}
