// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from dynamic.djinni

package co.ledger.core;

import java.util.concurrent.atomic.AtomicBoolean;

/**
 *Class representing an object that holds references to different types of objects,
 *those references are appended dynamically in an array like structure and can be retrieved by their index
 */
public abstract class DynamicArray {
    /**
     *Get count of stored references
     *@return 64 bits integer
     */
    public abstract long size();

    /**
     *Push a 32 bits integer
     *@param value, 32 bits integer
     *@return DynamicArray with value stored in it
     */
    public abstract DynamicArray pushInt(int value);

    /**
     *Push a 64 bits integer
     *@param value, 64 bits integer
     *@return DynamicArray with value stored in it
     */
    public abstract DynamicArray pushLong(long value);

    /**
     *Push a string
     *@param value, string
     *@return DynamicArray with value stored in it
     */
    public abstract DynamicArray pushString(String value);

    /**
     *Push a double
     *@param value, double
     *@return DynamicArray with value stored in it
     */
    public abstract DynamicArray pushDouble(double value);

    /**
     *Push a binary
     *@param value, binary
     *@return DynamicArray with value stored in it
     */
    public abstract DynamicArray pushData(byte[] value);

    /**
     *Push a bool
     *@param value, bool
     *@return DynamicArray with value stored in it
     */
    public abstract DynamicArray pushBoolean(boolean value);

    /**
     *Push a DynamicObject object
     *@param value, DynamicObject
     *@return DynamicArray with value stored in it
     */
    public abstract DynamicArray pushObject(DynamicObject value);

    /**
     *Push a DynamicArray object
     *@param value, DynamicArray
     *@return DynamicArray with value stored in it
     */
    public abstract DynamicArray pushArray(DynamicArray value);

    /**
     *Get string at a given index
     *@param index, 64 bits integer
     *@return Optional string
     */
    public abstract String getString(long index);

    /**
     *Get 32 bits integer at a given index
     *@param index, 64 bits integer
     *@return Optional 32 bits integer
     */
    public abstract Integer getInt(long index);

    /**
     *Get 64 bits integer at a given index
     *@param index, 64 bits integer
     *@return Optional 64 bits integer
     */
    public abstract Long getLong(long index);

    /**
     *Get double at a given index
     *@param index, 64 bits integer
     *@return Optional double
     */
    public abstract Double getDouble(long index);

    /**
     *Get binary at a given index
     *@param index, 64 bits integer
     *@return Optional binary
     */
    public abstract byte[] getData(long index);

    /**
     *Get bool at a given index
     *@param index, 64 bits integer
     *@return Optional bool
     */
    public abstract Boolean getBoolean(long index);

    /**
     *Get DynamicObject object at a given index
     *@param index, 64 bits integer
     *@return Optional DynamicObject
     */
    public abstract DynamicObject getObject(long index);

    /**
     *Get DynamicArray object at a given index
     *@param index, 64 bits integer
     *@return Optional DynamicArray
     */
    public abstract DynamicArray getArray(long index);

    /**
     *Concatenate current DynamicArray with another one
     *@param array, DynamicArray object to concatenate with
     *@return DynamicArray object, concatenated DynamicArray
     */
    public abstract DynamicArray concat(DynamicArray array);

    /**
     *Get type of value stored at a given index
     *@param index, 64 bits integer
     *@return Optional DynamicType enum entry
     */
    public abstract DynamicType getType(long index);

    /**
     *Delete value stored at given index
     *@param index, 64 bits integer
     *@return bool, true if deletion succeeded
     */
    public abstract boolean remove(long index);

    /**
     *Dump whole object's content as string
     *@return string
     */
    public abstract String dump();

    /**
     *Serialize whole object to a binary
     *@return binary
     */
    public abstract byte[] serialize();

    /**
     *Get readonly status of object
     *@param bool
     */
    public abstract boolean isReadOnly();

    /**
     *Create a new instance of DynamicArray class
     *@return DynamicArray instance
     */
    public static native DynamicArray newInstance();

    /**
     *Parse a binary to a DynamicArray
     *@param serialized, binary to parse
     *@return Optional DynamicArray
     */
    public static native DynamicArray load(byte[] serialized);

    private static final class CppProxy extends DynamicArray
    {
        private final long nativeRef;
        private final AtomicBoolean destroyed = new AtomicBoolean(false);

        private CppProxy(long nativeRef)
        {
            if (nativeRef == 0) throw new RuntimeException("nativeRef is zero");
            this.nativeRef = nativeRef;
        }

        private native void nativeDestroy(long nativeRef);
        public void destroy()
        {
            boolean destroyed = this.destroyed.getAndSet(true);
            if (!destroyed) nativeDestroy(this.nativeRef);
        }
        protected void finalize() throws java.lang.Throwable
        {
            destroy();
            super.finalize();
        }

        @Override
        public long size()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_size(this.nativeRef);
        }
        private native long native_size(long _nativeRef);

        @Override
        public DynamicArray pushInt(int value)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_pushInt(this.nativeRef, value);
        }
        private native DynamicArray native_pushInt(long _nativeRef, int value);

        @Override
        public DynamicArray pushLong(long value)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_pushLong(this.nativeRef, value);
        }
        private native DynamicArray native_pushLong(long _nativeRef, long value);

        @Override
        public DynamicArray pushString(String value)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_pushString(this.nativeRef, value);
        }
        private native DynamicArray native_pushString(long _nativeRef, String value);

        @Override
        public DynamicArray pushDouble(double value)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_pushDouble(this.nativeRef, value);
        }
        private native DynamicArray native_pushDouble(long _nativeRef, double value);

        @Override
        public DynamicArray pushData(byte[] value)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_pushData(this.nativeRef, value);
        }
        private native DynamicArray native_pushData(long _nativeRef, byte[] value);

        @Override
        public DynamicArray pushBoolean(boolean value)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_pushBoolean(this.nativeRef, value);
        }
        private native DynamicArray native_pushBoolean(long _nativeRef, boolean value);

        @Override
        public DynamicArray pushObject(DynamicObject value)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_pushObject(this.nativeRef, value);
        }
        private native DynamicArray native_pushObject(long _nativeRef, DynamicObject value);

        @Override
        public DynamicArray pushArray(DynamicArray value)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_pushArray(this.nativeRef, value);
        }
        private native DynamicArray native_pushArray(long _nativeRef, DynamicArray value);

        @Override
        public String getString(long index)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getString(this.nativeRef, index);
        }
        private native String native_getString(long _nativeRef, long index);

        @Override
        public Integer getInt(long index)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getInt(this.nativeRef, index);
        }
        private native Integer native_getInt(long _nativeRef, long index);

        @Override
        public Long getLong(long index)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getLong(this.nativeRef, index);
        }
        private native Long native_getLong(long _nativeRef, long index);

        @Override
        public Double getDouble(long index)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getDouble(this.nativeRef, index);
        }
        private native Double native_getDouble(long _nativeRef, long index);

        @Override
        public byte[] getData(long index)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getData(this.nativeRef, index);
        }
        private native byte[] native_getData(long _nativeRef, long index);

        @Override
        public Boolean getBoolean(long index)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getBoolean(this.nativeRef, index);
        }
        private native Boolean native_getBoolean(long _nativeRef, long index);

        @Override
        public DynamicObject getObject(long index)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getObject(this.nativeRef, index);
        }
        private native DynamicObject native_getObject(long _nativeRef, long index);

        @Override
        public DynamicArray getArray(long index)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getArray(this.nativeRef, index);
        }
        private native DynamicArray native_getArray(long _nativeRef, long index);

        @Override
        public DynamicArray concat(DynamicArray array)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_concat(this.nativeRef, array);
        }
        private native DynamicArray native_concat(long _nativeRef, DynamicArray array);

        @Override
        public DynamicType getType(long index)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getType(this.nativeRef, index);
        }
        private native DynamicType native_getType(long _nativeRef, long index);

        @Override
        public boolean remove(long index)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_remove(this.nativeRef, index);
        }
        private native boolean native_remove(long _nativeRef, long index);

        @Override
        public String dump()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_dump(this.nativeRef);
        }
        private native String native_dump(long _nativeRef);

        @Override
        public byte[] serialize()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_serialize(this.nativeRef);
        }
        private native byte[] native_serialize(long _nativeRef);

        @Override
        public boolean isReadOnly()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_isReadOnly(this.nativeRef);
        }
        private native boolean native_isReadOnly(long _nativeRef);
    }
}