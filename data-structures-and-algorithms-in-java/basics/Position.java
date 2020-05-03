package basics;

public interface Position<E> {
    E getElement() throws IllegalStateException;
}
