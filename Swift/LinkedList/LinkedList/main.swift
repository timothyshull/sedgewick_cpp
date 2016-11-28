//
//  main.swift
//  LinkedList
//
//  Created by Tim Shull on 11/27/16.
//  Copyright © 2016 Tim Shull. All rights reserved.
//

import Foundation

//import XCTest

//class LinkedListTest: XCTestCase {
//    let numbers = [8, 2, 10, 9, 7, 5]
//
//    fileprivate func buildList() -> LinkedList<Int> {
//        let list = LinkedList<Int>()
//        for number in numbers {
//            list.append(number)
//        }
//        return list
//    }
//
//    func testEmptyList() {
//        let list = LinkedList<Int>()
//        XCTAssertTrue(list.isEmpty)
//        XCTAssertEqual(list.count, 0)
//        XCTAssertNil(list.head)
//        XCTAssertNil(list.tail)
//    }
//
//    func testListWithOneElement() {
//        let list = LinkedList<Int>()
//        list.append(123)
//
//        XCTAssertFalse(list.isEmpty)
//        XCTAssertEqual(list.count, 1)
//
//        XCTAssertNotNil(list.head)
//        XCTAssertNil(list.head!.previous)
//        XCTAssertNil(list.head!.next)
//        XCTAssertEqual(list.head!.value, 123)
//
//        XCTAssertNotNil(list.tail)
//        XCTAssertNil(list.tail!.previous)
//        XCTAssertNil(list.tail!.next)
//        XCTAssertEqual(list.tail!.value, 123)
//
//        XCTAssertTrue(list.head === list.tail)
//    }
//
//    func testListWithTwoElements() {
//        let list = LinkedList<Int>()
//        list.append(123)
//        list.append(456)
//
//        XCTAssertEqual(list.count, 2)
//
//        XCTAssertNotNil(list.head)
//        XCTAssertEqual(list.head!.value, 123)
//
//        XCTAssertNotNil(list.tail)
//        XCTAssertEqual(list.tail!.value, 456)
//
//        XCTAssertTrue(list.head !== list.tail)
//
//        XCTAssertNil(list.head!.previous)
//        XCTAssertTrue(list.head!.next === list.tail)
//        XCTAssertTrue(list.tail!.previous === list.head)
//        XCTAssertNil(list.tail!.next)
//    }
//
//    func testListWithThreeElements() {
//        let list = LinkedList<Int>()
//        list.append(123)
//        list.append(456)
//        list.append(789)
//
//        XCTAssertEqual(list.count, 3)
//
//        XCTAssertNotNil(list.head)
//        XCTAssertEqual(list.head!.value, 123)
//
//        let second = list.head!.next
//        XCTAssertNotNil(second)
//        XCTAssertEqual(second!.value, 456)
//
//        XCTAssertNotNil(list.tail)
//        XCTAssertEqual(list.tail!.value, 789)
//
//        XCTAssertNil(list.head!.previous)
//        XCTAssertTrue(list.head!.next === second)
//        XCTAssertTrue(second!.previous === list.head)
//        XCTAssertTrue(second!.next === list.tail)
//        XCTAssertTrue(list.tail!.previous === second)
//        XCTAssertNil(list.tail!.next)
//    }
//
//    func testNodeAtIndexInEmptyList() {
//        let list = LinkedList<Int>()
//        let node = list.node(atIndex: 0)
//        XCTAssertNil(node)
//    }
//
//    func testNodeAtIndexInListWithOneElement() {
//        let list = LinkedList<Int>()
//        list.append(123)
//
//        let node = list.node(atIndex: 0)
//        XCTAssertNotNil(node)
//        XCTAssertEqual(node!.value, 123)
//        XCTAssertTrue(node === list.head)
//    }
//
//    func testNodeAtIndex() {
//        let list = buildList()
//
//        let nodeCount = list.count
//        XCTAssertEqual(nodeCount, numbers.count)
//
//        XCTAssertNil(list.node(atIndex: -1))
//        XCTAssertNil(list.node(atIndex: nodeCount))
//
//        let first = list.node(atIndex: 0)
//        XCTAssertNotNil(first)
//        XCTAssertTrue(first === list.head)
//        XCTAssertEqual(first!.value, numbers[0])
//
//        let last = list.node(atIndex: nodeCount - 1)
//        XCTAssertNotNil(last)
//        XCTAssertTrue(last === list.tail)
//        XCTAssertEqual(last!.value, numbers[nodeCount - 1])
//
//        for i in 0 ..< nodeCount {
//            let node = list.node(atIndex: i)
//            XCTAssertNotNil(node)
//            XCTAssertEqual(node!.value, numbers[i])
//        }
//    }
//
//    func testSubscript() {
//        let list = buildList()
//        for i in 0 ..< list.count {
//            XCTAssertEqual(list[i], numbers[i])
//        }
//    }
//
//    func testInsertAtIndexInEmptyList() {
//        let list = LinkedList<Int>()
//        list.insert(123, atIndex: 0)
//
//        XCTAssertFalse(list.isEmpty)
//        XCTAssertEqual(list.count, 1)
//
//        let node = list.node(atIndex: 0)
//        XCTAssertNotNil(node)
//        XCTAssertEqual(node!.value, 123)
//    }
//
//    func testInsertAtIndex() {
//        let list = buildList()
//        let prev = list.node(atIndex: 2)
//        let next = list.node(atIndex: 3)
//        let nodeCount = list.count
//
//        list.insert(444, atIndex: 3)
//
//        let node = list.node(atIndex: 3)
//        XCTAssertNotNil(node)
//        XCTAssertEqual(node!.value, 444)
//        XCTAssertEqual(nodeCount + 1, list.count)
//
//        XCTAssertFalse(prev === node)
//        XCTAssertFalse(next === node)
//        XCTAssertTrue(prev!.next === node)
//        XCTAssertTrue(next!.previous === node)
//    }
//
//    func testRemoveAtIndexOnListWithOneElement() {
//        let list = LinkedList<Int>()
//        list.append(123)
//
//        let value = list.remove(atIndex: 0)
//        XCTAssertEqual(value, 123)
//
//        XCTAssertTrue(list.isEmpty)
//        XCTAssertEqual(list.count, 0)
//        XCTAssertNil(list.head)
//        XCTAssertNil(list.tail)
//    }
//
//    func testRemoveAtIndex() {
//        let list = buildList()
//        let prev = list.node(atIndex: 2)
//        let next = list.node(atIndex: 3)
//        let nodeCount = list.count
//
//        list.insert(444, atIndex: 3)
//
//        let value = list.remove(atIndex: 3)
//        XCTAssertEqual(value, 444)
//
//        let node = list.node(atIndex: 3)
//        XCTAssertTrue(next === node)
//        XCTAssertTrue(prev!.next === node)
//        XCTAssertTrue(node!.previous === prev)
//        XCTAssertEqual(nodeCount, list.count)
//    }
//
//    func testRemoveLastOnListWithOneElement() {
//        let list = LinkedList<Int>()
//        list.append(123)
//
//        let value = list.removeLast()
//        XCTAssertEqual(value, 123)
//
//        XCTAssertTrue(list.isEmpty)
//        XCTAssertEqual(list.count, 0)
//        XCTAssertNil(list.head)
//        XCTAssertNil(list.tail)
//    }
//
//    func testRemoveLast() {
//        let list = buildList()
//        let last = list.tail
//        let prev = last!.previous
//        let nodeCount = list.count
//
//        let value = list.removeLast()
//        XCTAssertEqual(value, 5)
//
//        XCTAssertNil(last!.previous)
//        XCTAssertNil(last!.next)
//
//        XCTAssertNil(prev!.next)
//        XCTAssertTrue(list.tail === prev)
//        XCTAssertEqual(nodeCount - 1, list.count)
//    }
//
//    func testRemoveAll() {
//        let list = buildList()
//        list.removeAll()
//        XCTAssertTrue(list.isEmpty)
//        XCTAssertEqual(list.count, 0)
//        XCTAssertNil(list.head)
//        XCTAssertNil(list.tail)
//    }
//
//    func testReverseLinkedList() {
//        let list = buildList()
//        let first = list.head
//        let last = list.tail
//        let nodeCount = list.count
//
//        list.reverse()
//
//        XCTAssertTrue(first === list.tail)
//        XCTAssertTrue(last === list.head)
//        XCTAssertEqual(nodeCount, list.count)
//    }
//}

func linkedListMain() {
    print("Running the main function for a linked list")
    let list: LinkedList<String> = LinkedList()
    var inputString: String?
    repeat {
        print("Input a new string:")
        inputString = readLine(strippingNewline: true)?.trimmingCharacters(in: CharacterSet.whitespacesAndNewlines)
        if inputString != "" {
            list.append(inputString!)
        }
    } while inputString != nil && inputString != ""

    for elem in list {
        print(elem)
    }
}

linkedListMain()