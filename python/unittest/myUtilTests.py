import unittest
import myUtil
import os

"""
1. unittest 모듈 import
2. "unittest.TestCase"로부터 파생된 사용자 테스트 클래스를 만든다.
3. 테스트 클래스 안에 "test"로 시작하는 테스트 메서드를 생성. 
- 테스트 메서드에서는 일반적으로 테스트하려는 함수를 호출하고 그 결과값을 self.assert~~() 메서드(assertEqual, assertTrue, assertFalse 등 내장함수)를 통해 확인한다.
4. 테스트 클래스가 완성되면 unittest.main()을 호출해 테스트를 실행시킨다.
"""

class MyUtilTest(unittest.TestCase):
    testfile = 'test.txt'

    # Fixture - setUp, tearDown
    # 테스트 전 사전준비 작업을 하는 setUp 함수 생성
    def setUp(self):
        f = open(MyUtilTest.testfile, 'w')
        f.write('123456')
        f.close()

    # 사후 clean up 처리
    def tearDown(self):
        try:
            os.remove(MyUtilTest.testfile)
        except:
            pass

    # test
    def test_filelen(self):
        leng = myUtil.filelen(MyUtilTest.testfile)
        self.assertEqual(leng, 6)

    def test_count_in_file(self):
        cnt = myUtil.count_in_file(MyUtilTest.testfile, '0')
        self.assertEqual(cnt, 1)

# __name__은 현재 모듈의 이름을 담고 있는 내장변수. 모듈이 직접 실행되는 경우에 __name__은 '__main__'으로 설정됨.
# 다른 모듈에 의해 import 되는 경우에는 __name__이 __main__이 아님.
if __name__ == '__main__': # 모듈이 직접 실행되는지 알아보는 코
    unittest.main()
