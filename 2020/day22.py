#!/usr/bin/env python
# 
# ===============================================================
# ADVENT OF CODE
# ===============================================================
#   DAY 1   A: find two lines that sum to 2020 given input
#           B: find three lines that sum to 2020 given input
# ===============================================================

INPUTFILE = "day22.input"



def read_file(input_file, p1, p2):
    input = open(input_file, 'r')

    p1.clear()
    p2.clear()

    p = []
    count = 0
    for line in input:
        line = line.strip()
        if(line == "Player 1:"):
            p = p1
            continue
        elif(line == "Player 2:"):
            p = p2
            continue
        elif(line == ""):
            continue

        try:
            p.append(int(line))
            count += 1
        except:
            print("Bad input line:", line)
            exit()
    
    input.close()
    return count

def print_decks(p1, p2):
    print("Player 1:", p1)
    print("Player 2:", p2)

def play_round(p1, p2):
    c1 = p1.pop(0)
    c2 = p2.pop(0)

    if(c1 > c2):        # Player 1 wins round
        p1.append(c1)
        p1.append(c2)
    else:               # Player 2 wins round
        p2.append(c2)
        p2.append(c1)

def score_decks(p1, p2):
    s1 = 0
    s2 = 0

    if(len(p1) > 0):
        for i in range(len(p1)-1, -1, -1):
            s1 += p1[i] * (len(p1) - i)
            # print("s1 += p1[{}] * len(p1) - i          {:>6} +=  {} * ({} - {})".format(i, s1, p1[i], len(p1), i))

    if(len(p2) > 0):
        for i in range(len(p2)-1, -1, -1):
            s2 += p2[i] * (len(p2) - i)
            # print("s2 += p2[{}] * len(p2) - i          {:>6} +=  {} * ({} - {})".format(i, s2, p2[i], len(p2), i))

    return s1, s2

def add_cards(p):
    t = 0
    for c in p:
        t += c
    return t

def check_repeat_history(p1, p2, p1_hist, p2_hist):
    try:
        p1_hist.index(p1)
        p2_hist.index(p2)
        return True
    except:
        return False

def recursive_combat(player1, player2):
    p1_hist = []
    p2_hist = []
    while(len(player1) > 0 and len(player2)):
        # print_decks(player1, player2)
        # print()
        if(check_repeat_history(player1, player2, p1_hist, p2_hist)):
            # Player 1 wins, hands match previous round
            # print("Player 1 wins on repeat hands (infinite games).")
            # print("p1_hist:", p1_hist)
            # print("p2_hist:", p2_hist)
            return 1
        p1_hist.append(player1[:])
        p2_hist.append(player2[:])
        c1 = player1.pop(0)
        c2 = player2.pop(0)
        if(len(player1) >= c1 and len(player2) >= c2):
            # sub game
            # print("subgame")
            p1 = player1[:c1]
            p2 = player2[:c2]
            if(recursive_combat(p1, p2) == 1):
                # Player 1 wins round
                player1.append(c1)
                player1.append(c2)
            else:
                # Player 2 wins round
                player2.append(c2)
                player2.append(c1)
        else:
            if(c1 > c2):
                # Player 1 wins round
                player1.append(c1)
                player1.append(c2)
            else:
                # Player 2 wins round
                player2.append(c2)
                player2.append(c1)

    return 1 if len(player1) > 0 else 2



def main():
    player1 = []
    player2 = []

    
    # PART A
    c = read_file(INPUTFILE, player1, player2)
    print("Cards read:", c)
    print_decks(player1, player2)
    print()

    round = 0
    while(len(player1) > 0 and len(player2) > 0):
        play_round(player1, player2)
        round += 1

    print("Rounds played:", round)
    # print_decks(player1, player2)
    
    s1, s2 = score_decks(player1, player2)
    print("Player {} wins.".format((1 if s1 > 0 else 2)))
    print()
    print("PART A: winner's score: {}.".format(s1 if s1 > 0 else s2))
    print()

    # PART B
    read_file(INPUTFILE, player1, player2)
    winner = recursive_combat(player1, player2)
    s1, s2 = score_decks(player1, player2)
    print("Player {} wins.".format(winner))
    print_decks(player1, player2)
    print()
    print("PART B: winner's score: {}.".format(s1 if s1 > 0 else s2))



if __name__ == "__main__":
    main()