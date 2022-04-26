package org.example;

import io.vavr.Function1;
import io.vavr.Function2;

public class PartialApplication {
    public static void main(String[] args) {
        Function2<String, String, String> cheers = (s1, s2) -> String.format("%s %s", s1, s2);
        Function1<String, String> sayHello = cheers.apply("Hello");
        Function1<String, String> sayHola = cheers.apply("Hola");
        sayHola.apply("Juan");
        sayHello.apply("John");
    }
}
