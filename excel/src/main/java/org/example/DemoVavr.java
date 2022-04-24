package org.example;

import io.vavr.Function1;
import io.vavr.Function2;
import io.vavr.Function3;
import io.vavr.collection.Array;
import io.vavr.control.Option;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.function.Function;
import java.util.function.Supplier;
import java.util.stream.Stream;

public class DemoVavr {
    static final Logger logger  = LoggerFactory.getLogger(DemoVavr.class);
    public static void main(String[] args) {

//        Supplier<Double> rnd = () -> Math.random();
//        Array<Double> a = Array.fill(10, rnd);
//        a.forEach(e -> System.out.println(e));

//        Array.ofAll(Stream.iterate(1, v -> v + 1));
        Function<Integer, Integer> pow = (n) -> n * n;
        logger.info(pow.apply(2).toString());

//        Lifting

        Function1<String, String> toUpper = (s) -> {
            if (s.isEmpty()) throw new IllegalArgumentException("input can not be null");
            return s.toUpperCase();
        };
        Function1<String, String> trim = String::trim;
        Function1<String, String> cheers = (s) -> String.format("Hello %s", s);
        Function1<String, String> composedCheer = cheers.compose(trim).compose(toUpper);

        Function1<String, Option<String>> lifted = Function1.lift(composedCheer);
        logger.info(String.valueOf(lifted.apply("")));
        logger.info(String.valueOf(lifted.apply("  aogaeog  ")));
        Function2<String, String, String> cheers2 = (s1, s2) -> String.format("%s %s", s1, s2);
        Function1<String, String> sayHello = cheers2.apply("Hello");
        Function1<String, String> sayHola = cheers2.apply("Hola");

        Function3<Integer, Integer, Integer, Integer> sum = (a, b, c) -> a + b + c;
        Function1<Integer, Function1<Integer, Integer>> add2 = sum.curried().apply(2);
        Function1<Integer, Integer> add2And3 = add2.curried().apply(3);


    }
}
