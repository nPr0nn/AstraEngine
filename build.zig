
const std  = @import("std");

pub fn build(b: *std.Build) void {
    build_app(b);
}

// TODO: Comentar essa bagaça
pub fn build_app(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // Game
    const exe = b.addExecutable(.{
        .name = "Astra",
        .root_source_file = null,
        .target = target,
        .optimize = optimize,
    });
    exe.addObjectFile(.{ .cwd_relative = "ext/glfw/zig-out/lib/libglfw.a" });
    exe.addCSourceFiles(.{
        .files = &.{
            "ext/glad/glad.c",
            "src/main.c",
            "src/callbacks.c",
            "src/core.c",
        },
        .flags = &.{},
    });
    exe.linkLibC();
    b.installArtifact(exe);

    // Run
    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
