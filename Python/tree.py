def printTree(node):
    s = [node.value]
    if node.left is not None:
        s.append(printTree(node.left))
    else:
        s.append(None)
    if node.right is not None:
        s.append(printTree(node.right))
    else:
        s.append(None)
    return s


class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.left = None
        self.right = None
        self.height = 0


def insert(node, key, value):
    if key < node.key:
        if node.left is None:
            node.left = Node(key, value)
        else:
            insert(node.left, key, value)
    elif key >= node.key:
        if node.right is None:
            node.right = Node(key, value)
        else:
            insert(node.right, key, value)

    updateHeight(node)
    balance(node)


def search(node, key):
    if node is None:
        return None
    if node.key == key:
        return node
    if key < node.key:
        return search(node.left, key)
    else:
        return search(node.right, key)


def getMin(node):
    if node is None:
        return None
    if node.left is None:
        return node
    return getMin(node.left)


def getMax(node):
    if node is None:
        return None
    if node.right is None:
        return node
    return getMax(node.right)


def delete(node, key):
    if node is None:
        return None
    elif key < node.key:
        node.left = delete(node.left, key)
    elif key > node.key:
        node.right = delete(node.right, key)
    else:
        if node.left is None or node.right is None:
            if node.left is None:
                node = node.right
            else:
                node = node.left
        else:
            max_in_left = getMax(node.left)
            node.key = max_in_left.key
            node.value = max_in_left.value
            node.right = delete(node.right, max_in_left.key)
            node.left = delete(node.left, max_in_left.key)
    if node is not None:
        updateHeight(node)
        balance(node)
    return node


def updateHeight(node):
    node.height = max(getHeight(node.left), getHeight(node.right)) + 1


def getHeight(node):
    if node is None:
        return -1
    else:
        return node.height


def getBalance(node):
    if node is None:
        return 0
    else:
        return getHeight(node.right) - getHeight(node.left)


def balance(node):
    balance = getBalance(node)
    if balance == -2:
        if getBalance(node.left) == 1:
            leftRotate(node.left)
        rightRotate(node)
    elif balance == 2:
        if getBalance(node.right) == -1:
            rightRotate(node.right)
        leftRotate(node)


def swap(node_a, node_b):
    node_a.key, node_b.key = node_b.key, node_a.key
    node_a.value, node_b.value = node_b.value, node_a.value
    return node_a, node_b


def rightRotate(node):
    node, node.left = swap(node, node.left)
    buffer = node.right
    node.right = node.left
    node.left = node.right.left
    node.right.left = node.right.right
    node.right.right = buffer
    updateHeight(node.right)
    updateHeight(node)


def leftRotate(node):
    node, node.right = swap(node, node.right)
    buffer = node.left
    node.left = node.right
    node.right = node.left.right
    node.right.left = node.right.right
    node.left.right = node.left.left
    node.left.left = buffer
    updateHeight(node.left)
    updateHeight(node)


def symmetricalTree(node):
    if node is None:
        return
    symmetricalTree(node.left)
    print(node.value)
    symmetricalTree(node.right)


def reverseTree(node):
    if node is None:
        return
    reverseTree(node.left)
    reverseTree(node.right)
    print(node.value)


def straightTree(node):
    if node is None:
        return
    print(node.value)
    straightTree(node.left)
    straightTree(node.right)


if __name__ == "__main__":
    tree = Node(7, 7)
    insert(tree, 5, 5)
    insert(tree, 8, 8)
    insert(tree, 4, 4)
    insert(tree, 6, 6)
    print(straightTree(tree))

    # print([a := search(node, 6), a.value if a is not None else None][1])
