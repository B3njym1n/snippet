package org.example;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;

import java.util.Optional;

import static org.assertj.core.api.Assertions.assertThat;

@DisplayName("Writing assertions for objects")
public class ObjectAssertionTest {
    @Nested
    @DisplayName("When object is null")
    class WhenObjectIsNull {

        private final Object NULL = null;

        @Test
        @DisplayName("Should be null")
        void shouldBeNull() {
            assertThat(NULL).isNull();
        }
    }

//    Asserting That Two Objects or Values Are Equal
    @Nested
    @DisplayName("When two objects are equal")
    class WhenTwoObjectsAreEqual {

        @Nested
        @DisplayName("When objects are integers")
        class WhenObjectsAreIntegers {

            private final Integer ACTUAL = 9;
            private final Integer EXPECTED = 9;

            @Test
            @DisplayName("Should be equal")
            void shouldBeEqual() {
                assertThat(ACTUAL).isEqualByComparingTo(EXPECTED);
            }
        }
    }
//    Asserting Object References
    @Nested
    @DisplayName("When two objects refer to the same object")
    class WhenTwoObjectsReferToSameObject {

        private final Object ACTUAL = new Object();
        private final Object EXPECTED = ACTUAL;

        @Test
        @DisplayName("Should refer to the same object")
        void shouldReferToSameObject() {
            assertThat(ACTUAL).isSameAs(EXPECTED);
        }
    }

//    Asserting That Two Arrays Are Equal
    @Nested
    @DisplayName("When two arrays are equal")
    class WhenArraysAreEqual {

        @Nested
        @DisplayName("When arrays contain integers")
        class WhenArraysContainIntegers {

            final int[] ACTUAL = new int[]{2, 5, 7};
            final int[] EXPECTED = new int[]{2, 5, 7};

            @Test
            @DisplayName("Should contain the same integers")
            void shouldContainSameIntegers() {
                assertThat(ACTUAL).isEqualTo(EXPECTED);
            }
        }
    }
//    Writing Assertions for Optional Objects
    @Nested
    @DisplayName("When the optional is empty")
    class WhenOptionalIsEmpty {

        @Test
        @DisplayName("Should be empty")
        void shouldBeEmpty() {
            assertThat(Optional.empty()).isEmpty();
        }
    }
}


