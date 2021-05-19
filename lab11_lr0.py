# Find Closure
def closure(I, nonT):
    J = I

    for item in J:
        # print(item)
        index = item[1].index('.')
        if (index < (len(item[1]) - 1) and item[1][index + 1] in nonT):
            # print('item : ',item[1][index+1])
            for production in nonT[item[1][index + 1]]:
                if ([item[1][index + 1], str('.') + str(production)] not in J):
                    J.append([item[1][index + 1], str('.') + str(production)])
    return J


# Set of Canonical Items
state = []
I = []

def setOfItems(start, nonTer, ter):
    I.append(closure([['start', '.' + start + '$']], nonTer))
    # print(I)
    ter += list(nonTer.keys())
    # print("list of inputs : " , ter)
    for conI in I:
        for grammar in ter:
            if (grammar == '$'):
                continue
            # print("grammar : ",grammar)
            goto = False
            goto1 = False
            shift = False
            shift1 = False
            reduce = False
            close = []
            for item in conI:
                # print("item  : ",item)
                if (item[1].index('.') < (len(item[1]) - 1) and item[1][item[1].index('.') + 1] is grammar):
                    close.append(
                        [item[0], item[1][:item[1].index('.')] + grammar + '.' + item[1][item[1].index('.') + 2:]])
                # else:
            l = closure(close, nonTer)
            if (len(l) == 0):
                continue
            # print("closure : ", l)
            if (grammar in nonTer.keys()):
                goto1 = True
            else:
                shift1 = True
            if (l not in I):
                if (goto1):
                    state.append(['g', I.index(conI) + 1, len(I) + 1, grammar])
                    goto = True
                elif (shift1):
                    shift = True
                    state.append(['s', I.index(conI) + 1, len(I) + 1, grammar])
                I.append(l)

            else:
                if (goto1):
                    goto = True
                    state.append(['g', I.index(conI) + 1, I.index(l) + 1, grammar])
                elif (shift1):
                    shift = True
                    state.append(['s', I.index(conI) + 1, I.index(l) + 1, grammar])


# building the parse table
reduce = []
accept = -1


def toReduce(rule, accept, start):
    s = ['start', start + '.$']
    for parState in I:
        if (s in parState):
            accept = I.index(parState)
        for item in parState:
            if (item in rule):
                reduce[I.index(parState)].append(rule.index(item))

    return accept

symbolMap = dict()
parseTable = []


def createParseTable(ter):
    for i in state:
        parseTable[i[1] - 1][symbolMap[i[3]]] = i[0] + str(i[2] - 1)

    parseTable[accept][symbolMap['$']] = 'a'

    for i in reduce:
        if (len(i) > 0):
            for j in ter:
                parseTable[reduce.index(i)][symbolMap[j]] = 'r' + str(i[0])

terminals = []
nonTerminals = dict()
n = int(input("Enter No. of Non-Terminals  : "))

for i in range(n):
    ch = input("NonTerminals : ").strip()
    rules = input("Productions (if more than one seperate by '|') : ").split("|")
    nonTerminals[ch] = rules

terminals = input("Enter Terminals (seperate by '|') : ").split("|")

# Original grammar

S = input("Start Symbol :  ")
terminals += ['$']
print("The Grammar is :- ")
for i in nonTerminals.keys():
    print(i, "-->", end=' ')
    for j in nonTerminals[i]:
        print(j, end=' | ')
    print()

setOfItems(S, nonTerminals, terminals)
print("\nCanonicals Items : ")
for count, i in enumerate(I):
    print(f'I{count + 1}: {i}')

print("\nState Transitions : ")
for count, i in enumerate(state):
    print(count + 1, i)

rule = []
accept = -1

for i in nonTerminals.keys():
    for j in nonTerminals[i]:
        rule.append([i, j + str('.')])

print('Rule :')
for i in rule:
    print(i)

# find the reduction rules
reduce = [[] for i in range(len(I))]
accept = toReduce(rule, accept, S)

print("Reduce")
for count, i in enumerate(reduce):
    print(count + 1, i)

print("Accept State: ", accept + 1)

# parse Table
symbols = []
symbols += terminals

for count, i in enumerate(symbols):
    symbolMap[i] = count
print(symbols)

parseTable = [['-' for i in range(len(symbols))] for j in range(len(I))]

for i in nonTerminals.keys():
    terminals.remove(i)

createParseTable(terminals)

# Display parse table
print('\nLR(0) Parse Table')
print(" \t\t", end='')
for i in symbols:
    print(i, end='\t')

print('\n')
print('-' * 60)
for count, j in enumerate(parseTable):
    print(f'I({count + 1})', end='\t\t')
    for i in j:
        print(i, end='\t')
    print()
