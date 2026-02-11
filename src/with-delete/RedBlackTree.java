package com.maxgcoding.DS.impl;

import java.util.Iterator;
import java.util.LinkedList;

public class RedBlackTree<K extends Comparable<K>, V> implements Iterable<K> {
    private static final Boolean RED = true;
    private static final Boolean BLACK = false;
    private static class Node<K extends Comparable<K>, V> {
        K key;
        V value;
        int N;
        Boolean color;
        Node<K,V> left;
        Node<K,V> right;
        Node(K key, V value) {
            this.key = key;
            this.value = value;
            this.color = RED;
            this.N = 1;
            this.left = null;
            this.right = null;
        }
    }
    
    private Node<K,V> root;
    public RedBlackTree() {
        root = null;
    }
    public boolean isEmpty() {
        return root == null;
    }
    public int size() {
        return size(root);
    }
    public boolean contains(K key) {
        return find(key) != null;
    }
    public Iterator<K> iterator() {
        return keys().iterator();
    }
    public K min() {
        Node<K,V> x = root;
        while (x != null && x.left != null) {
            x = x.left;
        }
        return x == null ? null:x.key;
    }
    public K max() {
        Node<K,V> x = root;
        while (x != null && x.right != null) {
            x = x.right;
        }
        return x == null ? null:x.key;
    }
    public void eraseMin() {
        erase(min());
    }
    public void eraseMax() {
        erase(max());
    }
    public void insert(K key, V value) {
        root = putR(root, key, value);
        root.color = BLACK;
    }
    public V find(K key) {
        Node<K,V> x = root;
        while (x != null) {
            if (key == x.key)
                break;
            x = (key.compareTo(x.key) < 0) ? x.left:x.right;
        }
        return x == null ? null:x.value;
    } 
    public K get(int rank) {
        Node<K,V> x = select(root, rank);
        return x == null ? null:x.key;
    }
    public void erase(K key) {
        if (isEmpty())
            return;
        if (isBlack(root.left) && isBlack(root.right))
                root.color = RED;
        root = eraseR(root, key);
        if (root != null) {
            root.color = BLACK;
        }
    }
    public boolean validate() {
        Node<K,V> x = root;
        int bb = 0;
        while (x != null) {
            if (isBlack(x)) {
                bb++;
            }
            x = x.left;
        }
        return isRB(root, bb);
    }
    public void print() {
        preorder(root);
        System.out.println();
    }
    public Iterable<K> keys() {
        LinkedList<K> list = new LinkedList<>();
        collect(root, list);
        return list;
    }
    private void collect(Node<K,V> x, LinkedList<K> list) {
        if (x != null) {
            collect(x.left, list);
            list.add(x.key);
            collect(x.right, list);
        }
    }
    private int size(Node<K,V> h) {
        return h == null ? 0:h.N;
    }
    private Boolean isRed(Node<K,V> h) {
        return h == null ? false:h.color.equals(RED);
    }
    private Boolean isBlack(Node<K,V> h) {
        return !isRed(h);
    }
    private Node<K,V> colorFlip(Node<K,V> h) {
        h.color = !h.color;
        if (h.left != null) h.left.color = !h.left.color;
        if (h.right != null) h.right.color = !h.right.color;
        return h;
    }
    private Node<K,V> rotL(Node<K,V> h) {
        Node<K,V> x = h.right; 
        h.right = x.left; 
        x.left = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = 1 + size(h.left) + size(h.right);
        return x;
    }
    private Node<K,V> rotR(Node<K,V> h) {
        Node<K,V> x = h.left; 
        h.left = x.right; 
        x.right = h;
        x.color = h.color;
        h.color = RED;
        x.N = h.N;
        h.N = 1 + size(h.left) + size(h.right);
        return x;
    }
    private Node<K,V> fixInsert(Node<K,V> h) {
        if (isRed(h.left) && isRed(h.right)) {
            h = colorFlip(h);
        } else if (isRed(h.left)) {
            if (isRed(h.left.right)) {
                h.left = rotL(h.left);
                h = rotR(h);
            } else if (isRed(h.left.left)) {
                h = rotR(h);
            }
        } else if (isRed(h.right)) {
            if (isRed(h.right.left)) {
                h.right = rotR(h.right);
                h = rotL(h);
            } else if (isRed(h.right.right)) {
                h = rotL(h);
            }
        }
        return h;
    }
    private Node<K,V> putR(Node<K,V> h, K key, V value) {
        if (h == null) {
            return new Node<>(key, value);
        }
        if (key.equals(h.key)) {
            h.value = value;
            return h;
        }
        if (key.compareTo(h.key) < 0) {
            h.left = putR(h.left, key, value);
        } else {
            h.right = putR(h.right, key, value);
        }
        h.N = 1 + size(h.left) + size(h.right);
        return fixInsert(h);
    }
    private Node<K,V> eraseR(Node<K,V> h, K key) {
        if (h == null)
            return h;
        h = pushRedDown(h, key);
        if (key.compareTo(h.key) < 0) {
            h.left = eraseR(h.left, key);
        } else if (key.compareTo(h.key) > 0) {
            h.right = eraseR(h.right, key);
        } else {
            if (h.right == null) {
                h = h.left;
            } else {
                Node<K,V> t = min(h.right);
                h.key = t.key;
                h.right = eraseR(h.right, t.key);
            }
        }
        if (h != null) {
            h.N = 1 + size(h.left) + size(h.right);
        }
        return h;
    }
    private Node<K,V> min(Node<K,V> h) {
        if (h == null) {
            return h;
        }
        Node<K,V> x = h;
        while (x.left != null) x = x.left;
        return x;
    }
    private Node<K,V> pushRedDown(Node<K,V> p, K key) {
        boolean cmp = (key.compareTo(p.key) < 0);
        Node<K,V> x = cmp ? p.left:p.right;
        Node<K,V> s = cmp ? p.right:p.left;
        if (isBlack(x) && isRed(s)) {
            p = cmp ? rotL(p):rotR(p);
        }
        x = (cmp) ? p.left:p.right;
        if (x != null && isBlack(x) && isBlack(x.left) && isBlack(x.right)) {
            p = cmp ? pushLeft(p):pushRight(p);
        }
        return p;
    }
    private Node<K,V> pushRight(Node<K,V> h) {
        h = colorFlip(h);
        if (isRed(h.left) && isRed(h.left.right)) {
            h.left = rotL(h.left);
            h = rotR(h);
            h = colorFlip(h);
        } else if (isRed(h.left) && isRed(h.left.left)) {
            h = rotR(h);
            h = colorFlip(h);
        }
        return h;
    }
    private Node<K,V> pushLeft(Node<K,V> h) {
        h = colorFlip(h);
        if (isRed(h.right) && isRed(h.right.left)) {
            h.right = rotR(h.right);
            h = rotL(h);
            h = colorFlip(h);
        } else if (isRed(h.right) && isRed(h.right.right)) {
            h = rotL(h);
            h = colorFlip(h);
        }
        return h;
    }
    private boolean isRB(Node<K,V> h, int bb) {
        if (h == null) 
            return bb == 0;
        if (isBlack(h)) bb--;
        if (isRed(h) && (isRed(h.left) || isRed(h.right)))
            return false;
        if (h.left != null && h.key.compareTo(h.left.key) < 0)
                return false;
        if (h.right != null && h.key.compareTo(h.right.key) > 0)
                return false;
        return isRB(h.left, bb) && isRB(h.right, bb);
    }
    private void preorder(Node<K,V> h) {
        if (h != null) {
            System.out.print(h.key + " ");
            preorder(h.left);
            preorder(h.right);
        }
    }
    private Node<K,V> select(Node<K,V> h, int k) {
        if (h == null)
            return null;
        int t = (h.left != null) ? h.left.N:0;
        if (t > k) return select(h.left, k);
        if (t < k) return select(h.right, k - t - 1);
        return h;
    }
}