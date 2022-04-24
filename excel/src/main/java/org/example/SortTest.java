package org.example;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

public class SortTest {

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
        List<Item> list2 = list.stream().sorted((a, b) -> {
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
        list2.forEach(e -> System.out.println("code: " + e.code + " name: " + e.name));
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
