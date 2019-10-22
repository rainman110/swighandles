#!/usr/bin/env python
# -*- coding: utf-8 -*-

import unittest

import standard

class TestHandles(unittest.TestCase):
    def test_c_type(self):
        c = standard.getC()
        self.assertIsInstance(c, standard.C)

    def test_get_handle_a(self):
        a = standard.getHandleA()
        self.assertIsInstance(a, standard.A)

    def test_get_none_a(self):
        a = standard.getNone()
        self.assertIsNone(a)

    def test_inheritance(self):
        c = standard.getC()
        self.assertIsInstance(c, standard.A)
        self.assertIsInstance(c, standard.Standard_Transient)
        # This function accept a reference to an A type
        standard.simpleFunctionByRef(c)

        # this function accept a handle to an a type
        standard.simpleFunctionHandle(c)
        standard.simpleFunctionHandleRef(c)
        standard.simpleFunctionHandle(standard.C())
        standard.simpleFunctionHandleRef(standard.C("NewC"))

        with self.assertRaises(TypeError):
            standard.simpleFunctionHandle(standard.Standard_Transient())

        with self.assertRaises(TypeError):
            standard.simpleFunctionByRef(standard.Standard_Transient())

        with self.assertRaises(TypeError):
            standard.simpleFunctionHandleRef(standard.Standard_Transient())

    def test_downcast(self):
        # returns a handle to transient, not to a
        a = standard.getHandleATransient();
        self.assertIsInstance(a, standard.Standard_Transient)
        self.assertNotIsInstance(a, standard.A)

        a_new = standard.A.DownCast(a)
        self.assertIsNotNone(a_new)
        self.assertIsInstance(a_new, standard.Standard_Transient)
        self.assertIsInstance(a_new, standard.A)

        a_new2 = standard.Handle_A_DownCast(a)
        self.assertIsNotNone(a_new2)
        self.assertIsInstance(a_new2, standard.Standard_Transient)
        self.assertIsInstance(a_new2, standard.A)

    def test_downcast_incompatible(self):
        d = standard.D("D")
        self.assertIsInstance(d, standard.Standard_Transient)
        self.assertIsInstance(d, standard.A)
        self.assertNotIsInstance(d, standard.C)

        d_new = standard.Handle_C_DownCast(d)
        self.assertIsNone(d_new)

    def test_return_ref(self):
        # this test should make sure, that the program does not crash
        builder = standard.ABuilder()
        aref = builder.GetARef();
        del aref

        standard.ABuilder().GetARef().DoSomething()

    def test_base_type(self):
        d = standard.D("D")
        standard.acceptTransient(d)

    def test_create_pointer(self):
        a = standard.createA()
        self.assertIsNotNone(a)
        self.assertIsInstance(a, standard.A)

    def test_create_copy(self):
        a = standard.getCopyA()
        self.assertIsNotNone(a)
        self.assertIsInstance(a, standard.A)

    def test_create_handle_by_ref(self):
        a = standard.Handle_A()
        self.assertTrue(a.IsNull())
        standard.createAHandle(a)
        self.assertEqual(a.Value(), "CreateHandleA")


if __name__ == '__main__':
    unittest.main(exit=False)
    print("#transients alive: ", standard.Standard_Transient.GetNumAlive())




