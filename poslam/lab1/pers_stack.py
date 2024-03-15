class PersStack:
    def __init__(self) -> None:
        
        self.index: int = 0
        self.value = [None]
        self.prev = [None]

    def push(self, i: int, x: any) -> None:
        
        if i + 1 > len(self.value):
            self.prev.append(self.index)
        else:
            self.prev.append(i)
            
        self.value.append(x)

        self.index += 1


    def pop(self, i: int) -> any:
        
        index_of_prev = self.prev[-1 if i > self.index else i]

        self.value.append(self.value[index_of_prev])
        self.prev.append(self.prev[index_of_prev])

        return self.value[-1 if i > self.index else i]


test = PersStack()
test.push(1, 3)
test.push(2, 5)
test.pop(2)
test.push(3, 6)
test.push(5, 1)
test.pop(3)
test.pop(4)
test.push(7, 9)

print(test.value, test.prev)